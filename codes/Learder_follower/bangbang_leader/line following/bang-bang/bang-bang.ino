#include "linesensor.h"
#include "motors.h"
//#include "LEDs.h"
#define GAP 1285



LineSensor_c linesensor(GAP);
Motors_c motors;

void setup() {
  // put your setup code here, to run once:
  linesensor.initialise();
  motors.initialise();
  Serial.begin(9600);
  delay(5000);
}

void loop() {
  Bang_Bang();
}

void Bang_Bang() {
  int biasV = 20;
  if ( linesensor.lineDetected() ) {
    if(linesensor.readLineSensor(1)>=GAP){
      motors.setMotorPower(0.0, biasV);
      delay(100);
    }
    else if(linesensor.readLineSensor(3)>=GAP){
      motors.setMotorPower(biasV,0.0);
      delay(100);
    }else{
      motors.setMotorPower(biasV,biasV);
    }
  }
  else {
    while (true) {
      motors.setMotorPower(0.0, 0.0);
      delay(3000);
    }
  }
}
