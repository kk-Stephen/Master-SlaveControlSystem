#ifndef _RVE_H
#define _RVE_H


class RVE_c {
  public:
    volatile long count_now_L;
    float L_velocity;
    volatile long count_now_R;
    float R_velocity;
    int MOTOR_FREQUENCY;
    float lpf_l;
    float alpha_l;
    float lpf_r;
    float alpha_r;
    // Constructor, must exist.
    RVE_c(int frequency) {
      count_now_L = 0;
      L_velocity = 0;
      count_now_R = 0;
      R_velocity = 0;
      MOTOR_FREQUENCY = frequency;
      lpf_l = 0;
      alpha_l = 0.2;
      lpf_r = 0;
      alpha_r = 0.2;
    } 

    float getLeftVelocity(volatile long count_ISR_L){
      float change = (float)(count_ISR_L - count_now_L);
      L_velocity = change / (float)MOTOR_FREQUENCY;
      count_now_L = count_ISR_L;
      lpf_l = ( lpf_l * (1 - alpha_l ) ) + ( L_velocity * alpha_l );
    
      
      return lpf_l;
    }

    float getRightVelocity(volatile long count_ISR_R){
      float change = (float)(count_ISR_R - count_now_R);
      R_velocity = change / (float)MOTOR_FREQUENCY;
      count_now_R = count_ISR_R;
      lpf_r = ( lpf_r * (1 - alpha_r ) ) + ( R_velocity * alpha_r );
    
      
      return lpf_r;
    }
};



#endif
