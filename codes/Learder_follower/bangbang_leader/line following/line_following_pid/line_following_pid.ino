#include "linesensor.h"
#include "motors.h"
//#include "LEDs.h"
#include "encoders.h"
#include "RVE.h"
#include "pid.h"

#define Motor_p 0.5
#define Motor_i 0.005
#define Motor_d 0.0005

#define Weight_p 0.5
#define Weight_i 0.005
#define Weight_d 0.0005

float BiasVelocity = 0.3;
float MaxTurnVelocity = 0.1;

#define MOTOR_FREQUENCY 20

#define PID_FREQUENCY 20

#define GAP 1250//1250


LineSensor_c linesensor(GAP);
Motors_c motors;
PID_c PID_head(Weight_p,Weight_i,Weight_d,PID_FREQUENCY);
PID_c PID_l(Motor_p,Motor_i,Motor_d,PID_FREQUENCY);
PID_c PID_r(Motor_p,Motor_i,Motor_d,PID_FREQUENCY);
RVE_c RVE(MOTOR_FREQUENCY);

float W = 0;

float Left_Motor_Straight = 0;
float Right_Motor_Straight = 0;

float head_demand = 0;
float feedback_signal_head = 0;
float L_demand = BiasVelocity;
float feedback_signal_L = 0;
float R_demand = BiasVelocity;
float feedback_signal_R = 0;

unsigned long motor_update_ts;
unsigned long pid_update_ts;
unsigned long pid_reset_ts;

float left_velocity = 0;
float right_velocity = 0;

void setup() {
  // put your setup code here, to run once:
  setupEncoder0();//右轮
  setupEncoder1();
  linesensor.initialise();
  motors.initialise();
  motor_update_ts = millis();
  pid_update_ts = millis();
  pid_reset_ts = millis();
  Serial.begin(9600);
  delay(5000);
}

void loop() {
  LineFollowing();
  unsigned long current_ts = millis();
  if (current_ts - pid_reset_ts > 10000) {
    PID_l.reset();
    PID_r.reset();
    PID_head.reset();
    pid_reset_ts = millis();
  }
  if (current_ts - motor_update_ts > MOTOR_FREQUENCY) {
    left_velocity = RVE.getLeftVelocity(count_e1);
    right_velocity = RVE.getRightVelocity(count_e0);
    W = linesensor.weightedMesurement();
    motor_update_ts = millis();
  }
  if (current_ts - pid_update_ts > PID_FREQUENCY) {  
    feedback_signal_head = PID_head.UPDATE(head_demand , W);
    feedback_signal_L = PID_l.UPDATE(L_demand , left_velocity);
    feedback_signal_R = PID_r.UPDATE(R_demand , right_velocity);
    pid_update_ts = millis();
  }
  
  Left_Motor_Straight = PID_l.keepVelocity(feedback_signal_L, Left_Motor_Straight);
  Right_Motor_Straight = PID_r.keepVelocity(feedback_signal_R, Right_Motor_Straight);
  motors.setMotorPower(Left_Motor_Straight, Right_Motor_Straight);
}

void LineFollowing() {
  if ( linesensor.lineDetected() ) {
    L_demand = BiasVelocity + feedback_signal_head * MaxTurnVelocity;
    R_demand = BiasVelocity - feedback_signal_head * MaxTurnVelocity;
  }
  else{
    while(true){
      motors.setMotorPower(0, 0);
    }
  }
}
