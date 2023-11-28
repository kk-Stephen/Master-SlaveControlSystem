#include "motors.h"
#include "bumpsensor.h"
#include "encoders.h"
#include "kinematics.h"
# include <EEPROM.h>

//detect black and white
#define STOP 1400


//UPDATE TIME
#define BUMP_SENSOR_UPDATE 50
#define KINE_UPDATE 100

Motors_c motors;
BumpSensor_c bump_sensors;
Kinematics_c kinematics;

bool on_following;                           // on line or not
unsigned long line_sensor_ts, kine_ts;  // time stamp
float sens_val[2];                      // line sensors values
int eeprom_address;

//weighted leader
void weighted(float left, float right) {
  float sum = left + right;
  float R[2] = { left, right };
  float N[2];
  for (int n = 0; n < 2; n++) {
    N[n] = R[n] / sum;
    N[n] = N[n] * 2;
  }
  //h_m = N[1]-N[0];
  float w = N[1] - N[0];
  //Serial.println(w);
  motors.setMotorPower(20 - 6* w, 20 + 6 * w);
}

bool lineDetected() {
  for (int i = 0; i < 2; i++) {
    if (sens_val[i] > STOP)
    return true;
  }
  return false;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //delay(5000);
  Serial.println("***RESET***");
  // put your setup code here, to run once:
  line_sensor_ts = millis();
  kine_ts = millis();

  on_following = true;
  eeprom_address = 0;
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  Serial.println("EEPROM cleared!");

  setupEncoder0();
  setupEncoder1();
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( eeprom_address >= 1020) {
    while (1) {
      motors.setMotorPower(0.0, 0.0);
      //      Serial.println(eeprom_address);
    }
  }

  float elapsed_t;
  unsigned long current_ts;
  current_ts = millis();

  elapsed_t = current_ts - line_sensor_ts;

  if (elapsed_t > BUMP_SENSOR_UPDATE) {
    bump_sensors.readBumpSensor(2, sens_val);
    on_following = lineDetected();
    line_sensor_ts = millis();
  }

  elapsed_t = current_ts - kine_ts;
  //Update Kine
  if (elapsed_t > KINE_UPDATE) {
    kinematics.update();
    EEPROM.put( eeprom_address, float(kinematics.getTheta()));
    eeprom_address += sizeof(float);
    EEPROM.put( eeprom_address, float(kinematics.getX()));
    eeprom_address += sizeof(float);
    EEPROM.put( eeprom_address, float(kinematics.getY()));
    eeprom_address += sizeof(float);  
    kine_ts = millis();
  }

  if (on_following == true) {
    weighted(sens_val[0], sens_val[1]);
  } else {
    motors.setMotorPower(0.00, 0.00);
  }

  Serial.print("Left:");
  Serial.println(sens_val[0]);
  Serial.print("Right:");
  Serial.println(sens_val[1]);  

}
