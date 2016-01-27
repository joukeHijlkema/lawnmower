/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grasmaaier.items;

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.RaspiPin;
import com.pi4j.wiringpi.Gpio;
import com.pi4j.wiringpi.SoftPwm;
import grasmaaier.Grasmaaier;
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
public class Blades extends Thread {

  protected final Comunicator com;
  protected final String Name = "Blades";

  private static final int PIN_NUMBER = 1;

  public Blades() {
    com = new Comunicator() {
      @Override
      public void receive(Message msg) {
        Blades.Parse(msg);
      }
    };
    try {
      this.com.start(Name, Parameters.maaierChannel);
    } catch (Exception ex) {
      Logger.getLogger(Element.class.getName()).log(Level.SEVERE, null, ex);
    }

    Gpio.wiringPiSetup();
    SoftPwm.softPwmCreate(PIN_NUMBER, 0, 100);
    final GpioController gpio = GpioFactory.getInstance();
    final GpioPinDigitalOutput dir = gpio.provisionDigitalOutputPin(RaspiPin.GPIO_00, "PinDir", PinState.HIGH);

    com.send("Running");
  }

  /**
   *
   * @param msg
   */
  private static void Parse(Message msg) {
    System.out.println("Parse in Blades : " + msg.getSrc() + ":" + msg.getObject());
    String[] items = msg.getObject().toString().split(Grasmaaier.sep);
    if (items[0].equals("Blades")) {
      System.out.println("OK");
      switch (items[1]) {
        case "Start":
          Blades.startMotor();
          break;
        case "Stop":
          Blades.stopMotor();
          break;
      }
    }
  }

  private static void startMotor() {
    for (int i = 0; i < 101; i++) {
      try {
        setSpeed(i);
        sleep(10);
      } catch (InterruptedException ex) {
        Logger.getLogger(Blades.class.getName()).log(Level.SEVERE, null, ex);
      }
    }
  }

  private static void stopMotor() {
    setSpeed(0);
  }

  private static void setSpeed(int speed) {
    SoftPwm.softPwmWrite(PIN_NUMBER, speed);
  }

}
