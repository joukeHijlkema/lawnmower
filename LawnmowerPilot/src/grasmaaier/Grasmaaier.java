/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grasmaaier;

import grasmaaier.basics.Comunicator;
import grasmaaier.basics.Parameters;
import grasmaaier.items.Batterie;
import grasmaaier.items.Blades;
import grasmaaier.items.Propulsion;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jgroups.Message;

/**
 *
 * @author hylkema
 */
public class Grasmaaier {

  final public static String sep = ":";

  private static final Comunicator intercom = new Comunicator() {
    @Override
    public final void receive(Message msg) {
      Grasmaaier.parseInt(msg);
    }
  };

  private static final Comunicator extcom = new Comunicator() {
    @Override
    public final void receive(Message msg) {
      Grasmaaier.parseExt(msg);
    }
  };

//  private final Gps gps;
  private final Blades blades;
  private final Batterie batterie;
  private final Propulsion propulsion;

  public Grasmaaier() {
    try {
      Grasmaaier.intercom.start("Grasmaaier", Parameters.maaierChannel);
    } catch (Exception ex) {
      Logger.getLogger(Grasmaaier.class.getName()).log(Level.SEVERE, null, ex);
    }
    try {
      Grasmaaier.extcom.start("Grasmaaier", Parameters.pilotChannel);
    } catch (Exception ex) {
      Logger.getLogger(Grasmaaier.class.getName()).log(Level.SEVERE, null, ex);
    }
//    this.gps = new Gps();
    this.blades = new Blades();
    this.batterie = new Batterie();
    this.propulsion = new Propulsion();
  }

  private static void parseInt(Message msg) {
    System.out.println("received int : " + msg.getObject().toString() + " from " + msg.getSrc().toString());
    switch (msg.getSrc().toString()) {
      case "GPS":
        parseGPS(msg.getObject().toString());
        break;
      case "Blades":
        parseBlades(msg.getObject().toString());
        break;
      case "Batterie":
        parseBatterie(msg.getObject().toString());
        break;
      case "Propulsion":
        parsePropulsion(msg.getObject().toString());
        break;
    }
  }

  private static void parseGPS(String msg) {
    String[] items = msg.split(sep);
    switch (items[0]) {
      case "Running":
        extcom.send("GPS:Running");
        break;
    }
  }

  private static void parseBlades(String msg) {
    String[] items = msg.split(sep);
    switch (items[0]) {
      case "Running":
        extcom.send("Blades:Running");
        break;
    }
  }

  private static void parseBatterie(String msg) {
    String[] items = msg.split(sep);
    switch (items[0]) {
      case "Running":
        extcom.send("Batterie:Running");
        break;
    }
  }

  private static void parsePropulsion(String msg) {
    String[] items = msg.split(sep);
    switch (items[0]) {
      case "Running":
        extcom.send("Propulsion:Running");
        break;
    }
  }

  private static void parseExt(Message msg) {
    System.out.println("received ext : " + msg.getObject().toString() + " from " + msg.getSrc().toString());
    String[] items = msg.getObject().toString().split(Grasmaaier.sep);
    switch (items[0]) {
      case "Blades":
        parseExtBlades(items[1]);
        break;
    }
  }

  private static void parseExtBlades(String msg) {
    System.out.println("in parseExtBlades : "+msg);
    switch (msg) {
      case "Start":
        if (Controle("Blades", "Start"))  {
          intercom.send("Blades:Start");
        }
        break;
      case "Stop":
        intercom.send("Blades:Stop");
        break;
    }
  }
  private static boolean Controle(String blades, String start) {
    return true;
  }
  /**
   * @param args the command line arguments
   */
  public static void main(String[] args) {
    Grasmaaier grasmaaier = new Grasmaaier();
  }
}
