// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _PID_H
#define _PID_H

// Class to contain generic PID algorithm.
class PID_c {
  public:
    unsigned long pre_ts, ts;
    float p_term, i_term, d_term;
    float feedback_sig;
    float pre_e; //previous error
    float Kp, Ki, Kd;
    // Constructor, must exist.
    PID_c() {
    } 

    // intialise class variables and Kp.
    void initialise(float kp, float ki, float kd){
      Kp = 0.4;
      Ki = 0.0009;
      Kd = 6.0; 
      p_term = 0.00;
      feedback_sig = 0.00;
      pre_ts = millis();
    }

    //reset i_term and Dt to prevent extremely large i_term when stop 
    void reset(){
      i_term = 0.00;
      pre_ts = millis();
      Serial.println("Call reset");
    }

    float update( float demand, float measurement ){
      ts = millis();
      float e = demand - measurement; // error_signal = demand - measurement 
      pre_e = e;
      p_term = float(Kp) * float(e);
      i_term += Ki * e * float(ts - pre_ts);
      if (ts - pre_ts != 0 ){
        d_term = Kd * (e - pre_e) / float( ts - pre_ts ); // -Kd * (e - pre_e) / float( ts - pre_ts );
      }else{
        d_term = 0;
      }
      /*Serial.print("e:");
      Serial.print(e);
      Serial.print(",");
      Serial.print("ts - pre_ts:");
      Serial.print(float(ts - pre_ts));
      Serial.print(",");
      Serial.print("i_term:");
      Serial.print(i_term);
      Serial.print(",");*/
      feedback_sig = p_term + i_term + d_term;
      pre_ts = ts; // update time
      pre_e = e; // update error
      return (feedback_sig);
    }

};



#endif
