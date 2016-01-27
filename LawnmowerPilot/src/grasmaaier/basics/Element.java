/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grasmaaier.basics;

import java.util.logging.Level;
import java.util.logging.Logger;
import org.jgroups.Message;

/**
 *
 * @author hylkema
 */
public class Element extends Thread {

  protected Comunicator com;
  
  protected final String Name;

  public Element(String Name) {
    this.Name = Name;
    
  }

  private void Parse(Message msg) {
    System.out.println("Element : This should not happen !!! " + msg.getSrc() + ": " + msg.getObject());
  }
}
