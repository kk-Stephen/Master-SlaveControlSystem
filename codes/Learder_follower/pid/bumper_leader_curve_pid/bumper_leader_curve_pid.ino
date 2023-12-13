#include "linesensor.h"
#include "motors.h"
//#include "LEDs.h"
#include "encoders.h"
#include "RVE.h"
#include "pid.h"
#include "bumpsensors.h"
#include "kinematics.h"
#include <EEPROM.h>

#define Motor_p 0.5
#define Motor_i 0.006
#define Motor_d 0.00012

#define Weight_p 0.5
#define Weight_i 0.006
#define Weight_d 0.00012
float BiasVelocity = 0.5;
float MaxTurnVelocity = 0.5;

#define MOTOR_FREQUENCY 5

#define PID_FREQUENCY 5

#define KINE_UPDATE 1000

#define GAP 1250//1250


LineSensor_c linesensor(GAP);
Motors_c motors;
BumpSensors_c bumpsensors;
Kinematics_c kine;
int eeprom_address;
unsigned long kine_ts;

PID_c PID_head(Weight_p, Weight_i, Weight_d, PID_FREQUENCY);
PID_c PID_l(Motor_p, Motor_i, Motor_d, PID_FREQUENCY);
PID_c PID_r(Motor_p, Motor_i, Motor_d, PID_FREQUENCY);
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

int temp = 0;

void setup() {
  // put your setup code here, to run once:
  setupEncoder0();//右轮
  setupEncoder1();
  linesensor.initialise();
  bumpsensors.init();
  motors.initialise();
  motor_update_ts = millis();
  pid_update_ts = millis();
  pid_reset_ts = millis();
  eeprom_address = 0;
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }

  Serial.println("EEPROM cleared!");
  kine_ts = millis();
  Serial.begin(9600);
}

void loop() {
  if ( eeprom_address >= 1020) {
    while (1) {
      motors.setMotorPower(0.0, 0.0);
      //      Serial.println(eeprom_address);
    }
  }
  unsigned long current_ts = millis();
  if (current_ts - kine_ts > KINE_UPDATE) {
    kine.Update(count_e1, count_e0);
    EEPROM.put( eeprom_address, kine.getTheta());
    eeprom_address += sizeof(float);
    EEPROM.put( eeprom_address, kine.getX());
    eeprom_address += sizeof(float);
    EEPROM.put( eeprom_address, kine.getY());
    eeprom_address += sizeof(float);
    kine_ts = millis();
  }
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
    //    Serial.print( "left_velocity:" );
    //    Serial.print( left_velocity );
    //    Serial.print( "," );
    //    Serial.print( "right_velocity:" );
    //    Serial.println( right_velocity );
    //    Serial.print( "," );
    //    Serial.print( "W" );
    //    Serial.println( W );
    motor_update_ts = millis();
  }
  if (current_ts - pid_update_ts > PID_FREQUENCY) {
    feedback_signal_head = PID_head.UPDATE(head_demand , W);
    LineFollowing();
    feedback_signal_L = PID_l.UPDATE(L_demand , left_velocity);
    feedback_signal_R = PID_r.UPDATE(R_demand , right_velocity);
    //    Serial.print( "feedback_signal_L" );
    //    Serial.println( feedback_signal_L );
    //    Serial.print( "feedback_signal_R" );
    //    Serial.println( feedback_signal_R );
    pid_update_ts = millis();
  }

  Left_Motor_Straight = PID_l.keepVelocity(feedback_signal_L, Left_Motor_Straight);
  Right_Motor_Straight = PID_r.keepVelocity(feedback_signal_R, Right_Motor_Straight);
  Serial.print( Left_Motor_Straight );
  Serial.print( "，" );
  Serial.print( Right_Motor_Straight );
  Serial.print( "," );
  Serial.println( W );
  motors.setMotorPower(Left_Motor_Straight, Right_Motor_Straight);
}

void LineFollowing() {
  if ( linesensor.lineDetected() ) {
    L_demand = BiasVelocity + feedback_signal_head * MaxTurnVelocity;
    R_demand = BiasVelocity - feedback_signal_head * MaxTurnVelocity;
    //    Serial.print( "L_demand" );
    //    Serial.println( L_demand );
    //    Serial.print( "R_demand" );
    //    Serial.println( R_demand );
  }
  else {
    motors.setMotorPower(0, 0);
  }
}
