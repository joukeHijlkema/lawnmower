/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grasmaaier.com;

import java.util.ArrayList;
import java.util.List;
import org.zeromq.ZMQ;

/**
 *
 * @author hylkema
 */
public class MyListener extends Thread {

  ZMQ.Socket sink;
  public List<String> Messages;

  //  to allow for listeners
  private final List<TalkBack> listeners = new ArrayList<>();
  // An interface to be implemented by everyone interested in "Hello" events

  public interface TalkBack {
    void parse(String msg);
  }

  public MyListener(ZMQ.Socket _sink) {
    this.Messages = new ArrayList<>();
    this.sink = _sink;
  }

  public void addListener(TalkBack toAdd) {
    listeners.add(toAdd);
  }

  @Override
  public void run() {
    //  Save everything that arrives on pipe
    int counter = 0;
    while (true) {
      String msg = this.sink.recvStr();
      this.Messages.add(msg);
      System.out.println("received : " + msg);
      for (TalkBack hl : listeners) {
        hl.parse(msg);
      }
    }
  }

  boolean got(String line, boolean remove) {
    int i = this.Messages.indexOf(line);
    if (i > -1 && remove) {
      this.Messages.remove(i);
    }
    return (i > -1);
  }

  boolean got(String line) {
    return this.got(line, true);
  }

}
