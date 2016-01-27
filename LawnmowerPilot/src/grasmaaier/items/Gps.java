/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grasmaaier.items;

import grasmaaier.basics.Comunicator;
import grasmaaier.basics.Element;
import grasmaaier.basics.Parameters;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jgroups.Message;
import se.hirt.pi.adafruit.gps.GPS;
import se.hirt.pi.adafruit.gps.GPSListener;
import se.hirt.pi.adafruit.gps.PositionEvent;
import se.hirt.pi.adafruit.gps.VelocityEvent;

/**
 *
 * @author hylkema
 */
public class Gps extends Thread {

  protected final Comunicator com;
  protected final String Name = "Gps";
  private final GPS gps;

  public Gps() {
    com = new Comunicator() {
      @Override
      public void receive(Message msg) {
        Gps.Parse(msg);
      }
    };
    try {
      this.com.start(Name, Parameters.maaierChannel);
    } catch (Exception ex) {
      Logger.getLogger(Element.class.getName()).log(Level.SEVERE, null, ex);
    }
    this.gps = new GPS();
    this.gps.addListener(new GPSListener() {
      @Override
      public void onEvent(PositionEvent event) {
        com.send("Position:" + event.getLocation().getLatitude() + "," + event.getLocation().getLongitude());
      }
      @Override
      public void onEvent(VelocityEvent event) {
      }
    }
    );
    com.send("Running");
  }

  /**
   *
   * @param msg
   */
  private static void Parse(Message msg) {
    System.out.println("Parse in Gps");
  }

}
