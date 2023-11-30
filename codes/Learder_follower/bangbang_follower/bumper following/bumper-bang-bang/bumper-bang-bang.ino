#include "bumper.h"
#include "motors.h"
#define GAP 900
#define LOSS 8000
int AVE = 200;

BUMPER_c bumper(GAP, LOSS);
Motors_c motors;

void setup() {
  // put your setup code here, to run once:
  bumper.initialise();
  motors.initialise();
  Serial.begin(9600);
  delay(5000);
}

void loop() {
  Bang_Bang();
  Serial.print(bumper.readLineSensor(0));
    Serial.print("    ");
    Serial.println(bumper.readLineSensor(1));
}

void Bang_Bang() {
  int biasV = 25;
  int maxV = 50;
  int l_vel = 0;
  int r_vel = 0;
  if ( bumper.farEnough()) {
    if(bumper.readLineSensor(1)- bumper.readLineSensor(0)>=AVE){
      r_vel = maxV;
      l_vel = 0;
    }
    else if(bumper.readLineSensor(0)- bumper.readLineSensor(1)>=AVE){
      l_vel = maxV;
      r_vel = 0;
    }else{
      l_vel = biasV;
      r_vel = biasV;
    }
    motors.setMotorPower(l_vel, r_vel);
  }
  else {
    Serial.println("停");
      motors.setMotorPower(0, 0);
  }
}
