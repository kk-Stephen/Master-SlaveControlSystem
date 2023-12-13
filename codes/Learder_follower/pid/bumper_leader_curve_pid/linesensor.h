#ifndef _LINESENSOR_H
#define _LINESENSOR_H


// Class to operate the linesensor(s).
class LineSensor_c {
  public:
    static const int MAX_SENSORS = 5;
    int EMIT_PIN;
    int LS_LEFT_PIN;  // Complete for DN1 pin
    int LS_MIDLEFT_PIN;   // Complete for DN2 pin
    int LS_MIDDLE_PIN;   // Complete for DN3 pin
    int LS_MIDRIGHT_PIN;   // Complete for DN4 pin
    int LS_RIGHT_PIN;
    int ls_pins[MAX_SENSORS]; 
    int led_pins[3];
    int SensorsStillReading;
    bool sensorFinished[MAX_SENSORS]; 
    int GAP;

    int LED_R_PIN;
    int LED_Y_PIN;
    int LED_G_PIN;
    // Constructor, must exist.
    LineSensor_c(int gap) {
      EMIT_PIN = 11;
      LS_LEFT_PIN = 12;
      LS_MIDLEFT_PIN = A0;
      LS_MIDDLE_PIN = A2;
      LS_MIDRIGHT_PIN = A3;
      LS_RIGHT_PIN = A4;
      SensorsStillReading = MAX_SENSORS;
      ls_pins[0] = LS_LEFT_PIN;
      ls_pins[1] = LS_MIDLEFT_PIN;
      ls_pins[2] = LS_MIDDLE_PIN;
      ls_pins[3] = LS_MIDRIGHT_PIN;
      ls_pins[4] = LS_RIGHT_PIN;
      
      GAP = gap;

      LED_R_PIN = 17;
      LED_Y_PIN = 13;
      LED_G_PIN = 30;

      led_pins[0] = LED_Y_PIN;
      led_pins[1] = LED_G_PIN;
      led_pins[2] = LED_R_PIN;
      
    } 

    void initialise(){    
      pinMode( EMIT_PIN, INPUT ); // Set EMIT as an input (off)
      pinMode( ls_pins[5], INPUT );     // Set line sensor pin to input
      for (int i = 0; i < MAX_SENSORS; i++) {
        sensorFinished[i] = false;
      }
      pinMode(LED_R_PIN,OUTPUT);
      pinMode(LED_Y_PIN,OUTPUT);
      pinMode(LED_G_PIN,OUTPUT);
    }

    float readLineSensor( int number ) {
      if( number < 0 ) {
        return 0;
      }
      if( number > 4 ) {
        return 0;
      }

      pinMode( EMIT_PIN, OUTPUT );
      digitalWrite( EMIT_PIN, HIGH );

      pinMode( ls_pins[ number ], OUTPUT );

      digitalWrite( ls_pins[ number ], HIGH );
      delayMicroseconds( 10 );

      pinMode(ls_pins[ number ], INPUT);
      unsigned long start_time = micros();

      while( digitalRead( ls_pins[ number ] ) == HIGH ) {
          // Do nothing here (waiting).
      }

      unsigned long end_time = micros();

      pinMode( EMIT_PIN, INPUT );

      unsigned long elapsed_time = 0;
      elapsed_time = end_time - start_time;
      if(number == 1){
        if((float)elapsed_time >= GAP ){
          digitalWrite(led_pins[number - 1],HIGH);
        }
        else{
          digitalWrite(led_pins[number - 1],LOW);
        }
      }
      else if(number == 2){
        if((float)elapsed_time >= GAP ){
          digitalWrite(led_pins[number - 1],LOW);
        }
        else{
          digitalWrite(led_pins[number - 1],HIGH);
        }
      }
      else if(number == 3){
        if((float)elapsed_time >= GAP ){
          digitalWrite(led_pins[number - 1],LOW);
        }
        else{
          digitalWrite(led_pins[number - 1],HIGH);
        }
      }
      return (float)elapsed_time;
    }

    void readParallel(float* linesensor_result){
      pinMode( EMIT_PIN, OUTPUT );
      digitalWrite( EMIT_PIN, HIGH );
      for( int n = 0; n < MAX_SENSORS; n++ ){
        pinMode( ls_pins[ n ], OUTPUT );
        digitalWrite( ls_pins[ n ], HIGH );
      }
    
    
      delayMicroseconds( 10 );
      for( int n = 0; n < MAX_SENSORS; n++ ){
        pinMode(ls_pins[ n ], INPUT);
        sensorFinished[n] = false;
      }
      unsigned long start_time = micros();
      SensorsStillReading = MAX_SENSORS;
      while( SensorsStillReading > 0 ){
        for( int n = 0; n < MAX_SENSORS; n++ ){
          if(!sensorFinished[n]){
            if( digitalRead( ls_pins[ n ] ) == LOW ){
              unsigned long end_time = micros();
              unsigned long elapsed_time = end_time - start_time;
              linesensor_result[ n ] = (float)elapsed_time;
              SensorsStillReading = SensorsStillReading - 1;
              sensorFinished[n] = true;
            }
          }
        }
      }
      pinMode( EMIT_PIN, INPUT );
    }

    float weightedMesurement(){
      float R_1 = readLineSensor(1);
      float R_3 = readLineSensor(3);
      float Sum = R_1 + R_3;
      float N_1 = R_1 / Sum;
      float N_3 = R_3 / Sum;
      float W = N_1 - N_3; 
      return W * 2;//(0无需转动；-向右转；+向左转)
    }

    //暂时没想好
    bool lineDetected(){
      if (readLineSensor(2) >= GAP){

        return true;
      }
      else{
        return false;
      }
    }
};



#endif
