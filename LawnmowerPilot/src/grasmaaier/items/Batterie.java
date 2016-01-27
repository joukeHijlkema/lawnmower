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

/**
 *
 * @author hylkema
 */
public class Batterie extends Thread {

  protected final Comunicator com;
  protected final String Name = "Batterie";

  public Batterie() {
    com = new Comunicator() {
      @Override
      public void receive(Message msg) {
        Batterie.Parse(msg);
      }
    };
    try {
      this.com.start(Name, Parameters.maaierChannel);
    } catch (Exception ex) {
      Logger.getLogger(Element.class.getName()).log(Level.SEVERE, null, ex);
    }
    com.send("Running");
  }

  /**
   *
   * @param msg
   */
  private static void Parse(Message msg) {
    System.out.println("Parse in Batterie");
  }

}
