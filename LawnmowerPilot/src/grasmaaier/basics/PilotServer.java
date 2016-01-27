/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grasmaaier.basics;

import grasmaaier.Pilot;
import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jgroups.Message;

/**
 *
 * @author hylkema
 */
public class PilotServer extends Thread {

  private final String Name;
  private static final Comunicator myCom = new Comunicator() {
    @Override
    public void receive(Message msg) {
      PilotServer.parse(msg);
    }
  };
  private static final String sep = ":";

  public PilotServer() {
    this.Name = Parameters.pilotServerName;
    try {
      this.myCom.start(Name, Parameters.pilotChannel);
    } catch (Exception ex) {
      Logger.getLogger(PilotServer.class.getName()).log(Level.SEVERE, null, ex);
    }
  }

  private static void parse(Message msg) {
    System.out.println("received : " + msg.getObject().toString() + " from " + msg.getSrc().toString());
    if (msg.getSrc().toString().equals(Parameters.maaierName)) {
      String[] items = msg.getObject().toString().split(sep);
      System.out.println("items[0]=" + items[0]);
      switch (items[0]) {
        case "GPS":
          PilotServer.parseGps(Arrays.copyOfRange(items, 1, items.length));
          break;
        case "Blades":
          PilotServer.parseBlades(Arrays.copyOfRange(items, 1, items.length));
          break;
        case "Batterie":
          PilotServer.parseBatterie(Arrays.copyOfRange(items, 1, items.length));
          break;
        case "Propulsion":
          PilotServer.parsePropulsion(Arrays.copyOfRange(items, 1, items.length));
          break;
      }
    }
  }

  private static void parseGps(String[] msg) {
    System.out.println("parseGps : " + msg[0]);
    switch (msg[0]) {
      case "Running":
        System.out.println("switch led");
        Pilot.gpsLed.green();
        break;
      case "Position":
        String[] coords = msg[1].split(",");
        double lat = Double.parseDouble(coords[0]);
        double lon = Double.parseDouble(coords[1]);
        Pilot.moveMaaier(lat, lon);
        break;
    }
  }
  private static void parseBlades(String[] msg) {
    System.out.println("parseBlades : " + msg[0]);
    switch (msg[0]) {
      case "Running":
        System.out.println("switch led");
        Pilot.bladeMotorLed.green();
        break;
    }
  }
  private static void parseBatterie(String[] msg) {
    System.out.println("parseBatterie : " + msg[0]);
    switch (msg[0]) {
      case "Running":
        System.out.println("switch led");
        Pilot.batteryLed.green();
        break;
    }
  }
  private static void parsePropulsion(String[] msg) {
    System.out.println("parsePropulsion : " + msg[0]);
    switch (msg[0]) {
      case "Running":
        System.out.println("switch led");
        Pilot.motorLed.green();
        break;
    }
  }

  public void send(String msg) {
   myCom.send(msg);
  }

}
