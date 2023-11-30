#include "bumper.h"
#include "motors.h"
#include "encoders.h"
#include "kinematics.h"

#define GAP 900//1450
#define LOSS 8000
#define KINE_UPDATE 20
# include <EEPROM.h>
Kinematics_c kine;
int eeprom_address;
BUMPER_c bumper(GAP, LOSS);
Motors_c motors;

unsigned long kine_ts;
void setup() {
  // put your setup code here, to run once:
  setupEncoder0();//右轮
  setupEncoder1();
  bumper.initialise();
  motors.initialise();
  Serial.begin(9600);
  eeprom_address = 0;
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }

  Serial.println("EEPROM cleared!");
  kine_ts = millis();
  delay(5000);
}

void loop() {
  if ( eeprom_address >= 1020) {
    while (1) {
      motors.setMotorPower(0.0, 0.0);
      //      Serial.println(eeprom_address);
    }
  }
  unsigned long current_ts = millis();
  unsigned long elapsed_time = current_ts - kine_ts;
  if (elapsed_time >= KINE_UPDATE) {
    kine.Update(count_e1, count_e0);
    EEPROM.put( eeprom_address, kine.getTheta());
    eeprom_address += sizeof(float);
    EEPROM.put( eeprom_address, kine.getX());
    eeprom_address += sizeof(float);
    EEPROM.put( eeprom_address, kine.getY());
    eeprom_address += sizeof(float);
    kine_ts = millis();
  }
  LineFollowing();
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
    if (bumper.readLineSensor(0) <= 200 && bumper.readLineSensor(1) <= 200) {
      motors.setMotorPower(-15, -15);
      delay(3000);
    }
    else {
      motors.setMotorPower(0, 0);
    }
  }
}
