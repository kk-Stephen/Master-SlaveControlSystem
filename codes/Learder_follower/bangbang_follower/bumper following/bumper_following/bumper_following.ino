#include "bumper.h"
#include "motors.h"
#define GAP 1450
#define LOSS 8000

int EMIT_PIN = 11;
int BL_PIN = 4;
int BR_PIN = 5;
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

    LineFollowing();
    Serial.print(bumper.readLineSensor(0));
    Serial.print("    ");
    Serial.println(bumper.readLineSensor(1));
//  pinMode( EMIT_PIN, OUTPUT );
//  digitalWrite( EMIT_PIN, LOW );
//
//  pinMode( BL_PIN, OUTPUT );
//
//  digitalWrite( BL_PIN, HIGH );
//  pinMode( BR_PIN, OUTPUT );
//
//  digitalWrite( BR_PIN, HIGH );
////  motors.setMotorPower(15, -15);
////  delay(100);
////  motors.setMotorPower(0, 0);
////  delay(5000);
}

void LineFollowing() {
  if (bumper.farEnough()) {
    int BiasPWM = 20;
    int MaxTurnPWM = 40;
    float W;
    W = bumper.weightedMesurement();
    int LeftPWM = BiasPWM + (W * MaxTurnPWM);
    int RightPWM = BiasPWM - (W * MaxTurnPWM);
    motors.setMotorPower(LeftPWM, RightPWM);
  }
  else {
    if(bumper.readLineSensor(0)<=200 && bumper.readLineSensor(1)<=200){
      motors.setMotorPower(-15, -15);
      delay(3000);
    }
    else{
      motors.setMotorPower(0, 0);
    }
  }
}
