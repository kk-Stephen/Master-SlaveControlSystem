// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _MOTORS_H
#define _MOTORS_H

# define L_PWM_PIN 10
# define L_DIR_PIN 16
# define R_PWM_PIN 9
# define R_DIR_PIN 15

# define FWD LOW
# define REV HIGH

// Class to operate the motor(s).
class Motors_c {
  float left_pwm;
  float right_pwm;


  public:

    // Constructor, must exist.
    Motors_c() {
      initialise();
    } 

    // Use this function to 
    // initialise the pins and 
    // state of your motor(s).
    void initialise() {
      left_pwm = 0.00;
      right_pwm = 0.00;
      digitalWrite(L_DIR_PIN, FWD);
      digitalWrite(R_DIR_PIN, FWD);
    }

    // Write a function to operate
    // your motor(s)
    // ...
    void setMotorPower(float left, float right){
      //direction
      //left
      if (left < 0 ){
        digitalWrite(L_DIR_PIN, REV);
      }else{
        digitalWrite(L_DIR_PIN, FWD);
      }
      //right
      if (right < 0){
        digitalWrite(R_DIR_PIN, REV);
      }else{
        digitalWrite(R_DIR_PIN, FWD);
      }
      //judge the speed of left wheel
      //left_pwm = abs(left) / 0.74  * 49;
      left_pwm = abs(left);
      if (left_pwm < 12){
        left_pwm = 0;
      }
      if (left_pwm > 35){
        left_pwm = 30;
      }
      //judge the speed of right wheel
      right_pwm = abs(right);
      if (right_pwm < 14){
        right_pwm = 0;
      }
      if (right_pwm > 35){
        right_pwm = 35;
      }
      analogWrite( L_PWM_PIN, left_pwm);
      analogWrite( R_PWM_PIN, right_pwm);
    }
    
};



#endif
