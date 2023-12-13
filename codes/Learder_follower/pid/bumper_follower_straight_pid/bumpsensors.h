#define EMIT_PIN 11

class BumpSensors_c {
  private:
    int emit_pin;
    int BL_PIN = 4;   // Complete for DN1 pin
    int BR_PIN = 5;   // Complete for DN2 pin

    int bs_pins[5] = {BL_PIN,
                      BR_PIN,
                     };
    int active_middle = 1600;
    int GAP = 500;
    int LOSS = 8000;

  public:
    BumpSensors_c() {

    }

    void init() {
      emit_pin = EMIT_PIN;

      pinMode(emit_pin, INPUT);
      pinMode(BL_PIN, INPUT);
      pinMode(BR_PIN, INPUT);
    }

    float readBumpSensor(int number) {
      if ( number < 0 ) {
        return 0;
      }
      if ( number > 1 ) {
        return 0;
      }

      pinMode( emit_pin, OUTPUT );
      digitalWrite( emit_pin, LOW );

      pinMode( bs_pins[ number ], OUTPUT );

      digitalWrite( bs_pins[ number ], HIGH );
      delayMicroseconds( 10 );

      pinMode( bs_pins[ number ], INPUT );
      unsigned long start_time = micros();

      while ( digitalRead( bs_pins[ number ] ) == HIGH ) {
        // Do nothing here (waiting).
      }

      unsigned long end_time = micros();

      pinMode( emit_pin, INPUT );

      unsigned long elapsed_time = end_time - start_time;

      // Give the result back to wherever this
      // function was called from.
      return (float)elapsed_time;
    }

    float weightedMeasure() {
      //sensors reading
      float r[2];
      for (int i = 0; i < 2; i++) {
        r[i] = readBumpSensor( i );
      }
      float sum = r[0] + r[1];

      float n[2];
      for (int i = 0; i < 2; i++) {
        n[i] = r[i] / sum;
        n[i] = n[i] * 2;
      }

      //weight
      float w = n[0] - n[1];
      return w;
    }

    float DistanceMeasure() {
      //sensors reading
      float r[2];
      for (int i = 0; i < 2; i++) {
        r[i] = readBumpSensor( i );
      }
      float sum = r[0] + r[1];

      float a = ((sum - 2000) / 2000);
      return a;
    }

    bool farEnough() {
      if (readBumpSensor(0) <= GAP && readBumpSensor(1) <= GAP) {
        return false;
      } else {
        return true;
      }
    }

};
