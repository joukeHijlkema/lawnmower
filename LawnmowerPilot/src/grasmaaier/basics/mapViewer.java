/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grasmaaier.basics;

import java.awt.Color;
import org.openstreetmap.gui.jmapviewer.JMapViewer;
import org.openstreetmap.gui.jmapviewer.MapMarkerDot;

/**
 *
 * @author hylkema
 */
public class mapViewer extends JMapViewer {
  
  MapMarkerDot maaier;
  MapMarkerDot base;

  public mapViewer() {
    this.maaier = new MapMarkerDot(Color.YELLOW,0  , 0);
    this.base   = new MapMarkerDot(Color.BLUE,0  , 0);
    java.util.Properties systemProperties = System.getProperties();
//    systemProperties.setProperty("http.proxyHost", "minos.onecert.fr");
//    systemProperties.setProperty("http.proxyPort", "80");
    this.setZoomContolsVisible(false);
    
  }

  public void selectTile(double lat, double lon) {
    this.setDisplayPositionByLatLon(lat,lon, 18);
    this.moveMaaier(lat, lon);
  }
  
  public void moveMaaier(double lat, double lon) {
    System.out.println("move to : "+lat+","+lon);
    this.removeMapMarker(this.maaier);
    this.maaier = new MapMarkerDot(lat , lon);
    this.addMapMarker(this.maaier);
  }

  public void moveBase(double lat, double lon) {
    this.removeMapMarker(this.base);
    this.base = new MapMarkerDot(Color.BLUE,lat , lon);
    this.addMapMarker(this.base);
  }
  
}
