/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grasmaaier.com;

import grasmaaier.Pilot;
import grasmaaier.com.MyListener.TalkBack;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;
import org.zeromq.ZContext;
import org.zeromq.ZMQ;

/**
 *
 * @author hylkema
 */
public class NewComunicator extends Thread {

  ZMQ.Socket outSocket, inSocket;
  MyListener myListener;
  static final String OUT_AD = "tcp://*:4245";
//  static final String IN_AD = "tcp://127.0.0.1:4244";
  static final String IN_AD = "tcp://192.168.1.102:4244";
//  static final String IN_AD = "tcp://192.168.1.32:4244";
//  final String IN_AD = this.getIp();
//  static final String SINK_AD = "tcp://134.212.97.63:4243";
  static final String ID = "Pilot";
  static boolean allAboard = false;

  @Override
  public void run() {

    System.out.println("starting ...");
    ZContext ctx = new ZContext();

    this.outSocket = ctx.createSocket(ZMQ.PUB);
    this.outSocket.bind(OUT_AD);
    System.out.println("Out started on " + OUT_AD);

    this.inSocket = ctx.createSocket(ZMQ.PULL);
    this.inSocket.bind(IN_AD);
    System.out.println("In started on " + IN_AD);

    this.myListener = new MyListener(this.inSocket);
    this.myListener.start();
    System.out.println("com has started");

//    allAboard = this.pingClients();
  }

  public void send(String msg) {
    System.out.println("sending on " + OUT_AD + " : " + msg);
    this.outSocket.send(msg);
  }

  public void addListener(TalkBack listener) {
    this.myListener.addListener(listener);
  }

  public boolean pingClients() {
    while (!this.myListener.got("Blades:online")) {
    };
    Pilot.bladeMotorLed.green();
    while (!this.myListener.got("Battery:online")) {
    };
    Pilot.batteryLed.green();
    while (!this.myListener.got("Motor:online")) {
    };
    Pilot.motorLed.green();
    while (!this.myListener.got("GPS:online")) {
    };
    Pilot.gpsLed.green();

    return true;
  }

  private String getIp() {
    String IP;
    try {
      for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();) {
        NetworkInterface intf = en.nextElement();
        for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) {
          IP = enumIpAddr.nextElement().toString();
          System.out.println("IP = "+IP);
          if (IP.equals("/134.212.97.63")) return "127.0.0.1:4244";
          if (IP.equals("/192.168.1.102")) return "192.168.1.102:4244";
        }
      }
    } catch (SocketException e) {
      System.out.println(" (error retrieving network interface list)");
    }
    return "0.0.0.0";
  }
}
