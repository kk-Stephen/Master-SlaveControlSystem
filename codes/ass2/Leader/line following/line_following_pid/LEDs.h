#ifndef _LED_H
#define _LED_H

// Class to contain generic PID algorithm.
class LED_c {
  public:
    int LED_R_PIN;
    int LED_Y_PIN;
    int LED_G_PIN;
    // Constructor, must exist.
    LED_c() {
      LED_R_PIN = 17;
      LED_Y_PIN = 13;
      LED_G_PIN = 30;
    }
    void initialise(){
      pinMode(LED_R_PIN,OUTPUT);
      pinMode(LED_Y_PIN,OUTPUT);
      pinMode(LED_G_PIN,OUTPUT);
    }

    void turnRed(int duration){
      digitalWrite(LED_R_PIN,HIGH);
      delay(duration);
      digitalWrite(LED_R_PIN,LOW);
    }

    void turnYellow(int duration){
      digitalWrite(LED_Y_PIN,HIGH);
      delay(duration);
      digitalWrite(LED_Y_PIN,LOW);
    }

    void turnGreen(int duration){
      digitalWrite(LED_G_PIN,HIGH);
      delay(duration);
      digitalWrite(LED_G_PIN,LOW);
    }

    void allOn(){
      turnRed(1000);
      turnYellow(1000);
      turnGreen(1000);
    }

};



#endif
