// this #ifndef stops this file
// from being included mored than
// once by the compiler.
#ifndef _PID_H
#define _PID_H

// Class to contain generic PID algorithm.
class PID_c {
  public:
    //p
    float p_term;
    float K_p;
    //i
    float i_term;
    float K_i;
    float derta_t;
    //d
    float d_term;
    float K_d;

    float feedback_signal;

    float error_signal_before;
    // Constructor, must exist.
    PID_c(float p, float i, float d, float derta_T) {
      p_term = 0;
      i_term = 0;
      d_term = 0;
      K_p = p;//0.5;//待定：0.5可以巡线0.025效果最好，但只是p，无id
      K_i = i;//0.005;//0.005
      K_d = d;//0.0005;//0.0005
      derta_t = derta_T * 0.001;

      error_signal_before = 0;
      feedback_signal = 0;
    }

    float UPDATE(float demand, float measurement) {
      float error_signal = demand - measurement;
      //p
      p_term = K_p * error_signal;
      //i
      i_term = i_term + K_i * error_signal * derta_t;
      //d
      d_term = K_d * (error_signal - error_signal_before) / derta_t;
      feedback_signal = p_term + i_term - d_term;
      error_signal_before = error_signal;
      return feedback_signal;
    }

    float keepVelocity(float gap, float velocity_now) {
      velocity_now = velocity_now + gap;
      return velocity_now;
    }
    void reset() {
      i_term = 0;
    }
};



#endif
