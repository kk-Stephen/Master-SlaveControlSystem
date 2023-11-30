#include "bumper.h"
#include "motors.h"
#include "encoders.h"
#include "kinematics.h"
# include <EEPROM.h>
#define GAP 900
#define LOSS 8000
int AVE = 200;
#define KINE_UPDATE 20
BUMPER_c bumper(GAP, LOSS);
Motors_c motors;
int eeprom_address;
Kinematics_c kine;
unsigned long kine_ts;
void setup() {
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
  Bang_Bang();
  //  Serial.print(bumper.readLineSensor(0));
  //    Serial.print("    ");
  //    Serial.println(bumper.readLineSensor(1));
}

void Bang_Bang() {
  int biasV = 25;
  int maxV = 50;
  int l_vel = 0;
  int r_vel = 0;
  if ( bumper.farEnough()) {
    if (bumper.readLineSensor(1) - bumper.readLineSensor(0) >= AVE) {
      r_vel = maxV;
      l_vel = 0;
    }
    else if (bumper.readLineSensor(0) - bumper.readLineSensor(1) >= AVE) {
      l_vel = maxV;
      r_vel = 0;
    } else {
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
