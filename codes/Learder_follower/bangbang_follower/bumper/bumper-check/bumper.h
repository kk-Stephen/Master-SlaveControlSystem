#ifndef _BUMPER_H
#define _BUMPER_H


// Class to operate the linesensor(s).
class BUMPER_c {
  public:
    static const int MAX_SENSORS = 2;
    int EMIT_PIN;
    int BL_PIN;  // Complete for DN1 pin
    int BR_PIN;   // Complete for DN2 pin
    int ls_pins[MAX_SENSORS];
    int SensorsStillReading;
    bool sensorFinished[MAX_SENSORS];
    int GAP;
    int LOSS;

    int LED_R_PIN;
    int LED_Y_PIN;
    int LED_G_PIN;
    // Constructor, must exist.
    BUMPER_c(int gap, int loss) {
      EMIT_PIN = 11;
      BL_PIN = 4;
      BR_PIN = 5;
      SensorsStillReading = MAX_SENSORS;
      ls_pins[0] = BL_PIN;
      ls_pins[1] = BR_PIN;
      GAP = gap;
      LOSS = loss;
      LED_R_PIN = 17;
      LED_Y_PIN = 13;
      LED_G_PIN = 30;
    }

    void initialise() {
      pinMode( EMIT_PIN, INPUT ); // Set EMIT as an input (off)
      pinMode( ls_pins[2], INPUT );     // Set line sensor pin to input
      for (int i = 0; i < MAX_SENSORS; i++) {
        sensorFinished[i] = false;
      }
      pinMode(LED_R_PIN, OUTPUT);
      pinMode(LED_Y_PIN, OUTPUT);
      pinMode(LED_G_PIN, OUTPUT);
    }

    float readLineSensor( int number ) {
      if ( number < 0 ) {
        return 0;
      }
      if ( number > 1 ) {
        return 0;
      }

      pinMode( EMIT_PIN, OUTPUT );
      digitalWrite( EMIT_PIN, LOW );

      pinMode( ls_pins[ number ], OUTPUT );

      digitalWrite( ls_pins[ number ], HIGH );
      delayMicroseconds( 10 );

      pinMode(ls_pins[ number ], INPUT);
      unsigned long start_time = micros();

      while ( digitalRead( ls_pins[ number ] ) == HIGH ) {
        // Do nothing here (waiting).
      }

      unsigned long end_time = micros();

      pinMode( EMIT_PIN, INPUT );

      unsigned long elapsed_time = end_time - start_time;
      switch (number) {
        case 0:
          if (elapsed_time >= GAP) {
            digitalWrite(LED_Y_PIN, HIGH);
          }
          else {
            digitalWrite(LED_Y_PIN, LOW);
          }
          break;
        case 1:
          if (elapsed_time >= GAP) {
            digitalWrite(LED_R_PIN, HIGH);
          }
          else {
            digitalWrite(LED_R_PIN, LOW);
          }
          break;
        default:
          break;
      }
      return (float)elapsed_time;
    }

    float weightedMesurement() {
      float R_0 = readLineSensor(0);
      float R_1 = readLineSensor(1);
      float Sum = R_0 + R_1;
      float N_0 = R_0 / Sum;
      float N_1 = R_1 / Sum;
      float W = N_0 - N_1;
      return W * 2;//(0无需转动；+向右转；-向左转)
    }
    bool farEnough() {
      if (readLineSensor(0) <= GAP || readLineSensor(1) <= GAP) {
        return false;
      }
      else if (readLineSensor(0) >= LOSS || readLineSensor(1) >= LOSS){
        return false;
      }
      else {
        return true;
      }
    }
    
};



#endif