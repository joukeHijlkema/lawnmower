/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grasmaaier.com;

import grasmaaier.Pilot;
import java.util.TimerTask;

/**
 *
 * @author hylkema
 */
public class checkComponents extends TimerTask{
  
  private NewComunicator myCom;

  public checkComponents(NewComunicator myCom) {
    this.myCom = myCom;
  }
  

  @Override
  public void run() {
    
    boolean allIsWell = true;
    
    this.myCom.send("Global:Alive?");
    
    if (this.myCom.myListener.got("GpsBase:Alive")) {
      Pilot.gpsBaseLed.green();
    } else {
      Pilot.gpsBaseLed.red();
    }
  }
}
