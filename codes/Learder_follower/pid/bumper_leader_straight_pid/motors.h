#ifndef _MOTORS_H
#define _MOTORS_H

//阶段一：设置速度，返回速度
//阶段二：左转右转：输入角度和左转右转
//阶段三：更多...

# define FWD LOW
# define REV HIGH

class Motors_c {
  public:
  int L_PWM_PIN;
  int L_DIR_PIN;
  int R_PWM_PIN;
  int R_DIR_PIN;
  float L_POWER;
  float R_POWER;
    // Constructor, must exist.
    Motors_c() {
      L_PWM_PIN=10;
      L_DIR_PIN=16;
      R_PWM_PIN=9;
      R_DIR_PIN=15;
    } 

    // Use this function to 
    // initialise the pins and 
    // state of your motor(s).
    void initialise() {
      pinMode(L_PWM_PIN, OUTPUT);
      pinMode(L_DIR_PIN, OUTPUT);
      pinMode(R_PWM_PIN, OUTPUT);
      pinMode(R_DIR_PIN, OUTPUT);

      L_POWER = 0;
      R_POWER = 0;
      
      digitalWrite(L_DIR_PIN,FWD);
      digitalWrite(R_DIR_PIN,FWD);

      analogWrite(L_PWM_PIN,0);
      analogWrite(R_PWM_PIN,0);
    }

    //set the speed of them
    void setMotorPower( float left_pwm, float right_pwm ){
      if (left_pwm >0){
          digitalWrite(L_DIR_PIN,FWD);
      }
      else{
          left_pwm = -1*left_pwm;
          digitalWrite(L_DIR_PIN,REV);
      }
      if (right_pwm >0){
          digitalWrite(R_DIR_PIN,FWD);
      }
      else{
          right_pwm = -1*right_pwm;
          digitalWrite(R_DIR_PIN,REV);
      }
      L_POWER = left_pwm;
      R_POWER = right_pwm;
     
      
      analogWrite(L_PWM_PIN,left_pwm);
      analogWrite(R_PWM_PIN,right_pwm);
    }
    
};



#endif
