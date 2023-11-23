// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _LINESENSOR_H
#define _LINESENSOR_H

# define EMIT_PIN    11    // Documentation says 11.
# define L_BUMP_PIN  4  //For DN1 pin
# define R_BUMP_PIN  5 //For DN2 pin

int bs_pins[2] = {L_BUMP_PIN,
                  R_BUMP_PIN}; //The sensors pin array

// Class to operate the linesensor(s).
class BumpSensor_c {
  float elapsed_time[2];
  public:

    // Constructor, must exist.
    LineSensor_c() {
      initialise();
    }

    void initialise(){
      //intialize pinMode as INPUT
      pinMode(EMIT_PIN, INPUT);
      for (int i = 0; i < 2; i++){
        pinMode(bs_pins[i], INPUT);
        set_time(0.00, i);
      }
    } 

    void get_time(float records[2]){
      //getter
      for (int i = 0; i < 2; i++){
        records[i] = elapsed_time[i];
      }
    }

    void set_time(float time, int i){
      //setter
      elapsed_time[i] = time;
    }

    void readBumpSensor(int number, float records[2]){
      //Open EMIT
      pinMode( EMIT_PIN, OUTPUT );
      digitalWrite( EMIT_PIN, LOW );

      //Charging n sensors
      for (int i = 0; i < number; i++){
        pinMode( bs_pins[i], OUTPUT );
        digitalWrite( bs_pins[i], HIGH );
      }
      delayMicroseconds( 10 );

      //Discharging n sensors
      for (int i = 0; i < number; i++){
        pinMode( bs_pins[i], INPUT );
      }

      unsigned long start_time = micros();

      //record elapsed time

      int sens_read = number; // No of linesensors need to be recorded

      while (sens_read > 0){ // no linesensor need to be recorded --> out

        for (int i = 0; i < number; i++){ // iterate all linesensors
          
          if (elapsed_time[i] == 0.00){ // initial value is 0.00
              
            if (micros() - start_time < 8000){ 
              // not overtime
              if (digitalRead(bs_pins[i]) == LOW){
                // discharging complete
                unsigned long end_time = micros();
                set_time(end_time - start_time, i);
                sens_read -= 1;
              }
              // if discharging did not complete do nothing
            }else{
              //overtime
              set_time(8000.00, i);//set time as 2500
              sens_read -= 1;
            }
          }
        }
      }
      
      get_time(records);// return array elapsed_time to results
      initialise(); //Close EMIT and initialize
    }  
};


#endif
