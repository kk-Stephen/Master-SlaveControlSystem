// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _LINESENSOR_H
#define _LINESENSOR_H

# define EMIT_PIN    11    // Documentation says 11.
# define LS_LEFT_PIN  12  //For DN1 pin
# define LS_MIDLEFT_PIN  A0 //For DN2 pin
# define LS_MIDDLE_PIN  A2 //For DN3 pin
# define LS_MIDRIGHT_PIN  A3 //For DN4 pin
# define LS_RIGHT_PIN  A4 //For DN5 pin

int ls_pins[5] = {LS_MIDLEFT_PIN,
                  LS_MIDDLE_PIN,
                  LS_MIDRIGHT_PIN,
                  LS_LEFT_PIN,
                  LS_RIGHT_PIN }; //The sensors pin array

// Class to operate the linesensor(s).
class LineSensor_c {
  float elapsed_time[5];
  public:

    // Constructor, must exist.
    LineSensor_c() {
      initialise();
    }

    void initialise(){
      //intialize pinMode as INPUT
      pinMode(EMIT_PIN, INPUT);
      for (int i = 0; i < 5; i++){
        pinMode(ls_pins[i], INPUT);
        set_time(0.00, i);
      }
    } 

    void get_time(float records[5]){
      //getter
      for (int i = 0; i < 5; i++){
        records[i] = elapsed_time[i];
      }
    }

    void set_time(float time, int i){
      //setter
      elapsed_time[i] = time;
    }

    void readLineSensor(int number, float records[5]){
      //Open EMIT
      pinMode( EMIT_PIN, OUTPUT );
      digitalWrite( EMIT_PIN, HIGH );

      //Charging n sensors
      for (int i = 0; i < number; i++){
        pinMode( ls_pins[i], OUTPUT );
        digitalWrite( ls_pins[i], HIGH );
      }
      delayMicroseconds( 10 );

      //Discharging n sensors
      for (int i = 0; i < number; i++){
        pinMode( ls_pins[i], INPUT );
      }

      unsigned long start_time = micros();

      //record elapsed time

      int sens_read = number; // No of linesensors need to be recorded

      while (sens_read > 0){ // no linesensor need to be recorded --> out

        for (int i = 0; i < number; i++){ // iterate all linesensors
          
          if (elapsed_time[i] == 0.00){ // initial value is 0.00
              
            if (micros() - start_time < 2500){ 
              // not overtime
              if (digitalRead(ls_pins[i]) == LOW){
                // discharging complete
                unsigned long end_time = micros();
                set_time(end_time - start_time, i);
                sens_read -= 1;
              }
              // if discharging did not complete do nothing
            }else{
              //overtime
              set_time(2500.00, i);//set time as 2500
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
