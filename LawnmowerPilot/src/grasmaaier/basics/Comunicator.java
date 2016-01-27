/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grasmaaier.basics;

import java.util.logging.Level;
import java.util.logging.Logger;
import org.jgroups.JChannel;
import org.jgroups.Message;
import org.jgroups.ReceiverAdapter;
import org.jgroups.View;

/**
 *
 * @author hylkema
 */
public class Comunicator extends ReceiverAdapter {

  JChannel channel;
  String user_name = System.getProperty("user.name", "n/a");
  public boolean connected = false;
  

  public void start(String Name, String Channel) throws Exception {
    channel = new JChannel(); // use the default config, udp.xml
    channel.setName(Name);
    channel.connect(Channel);
    channel.setReceiver(this);
  }

  @Override
  public void viewAccepted(View new_view) {
    System.out.println("** view: " + new_view);
  }

  @Override
  public void receive(Message msg) {
    System.out.println("This should not happen !!! "+this.channel.getName()+" <- "+msg.getSrc() + ": " + msg.getObject());
  }

  public void send(String msg) {
    try {
      channel.send(new Message(null, null, msg));
    } catch (Exception ex) {
      Logger.getLogger(Comunicator.class.getName()).log(Level.SEVERE, null, ex);
    }
  }
}
