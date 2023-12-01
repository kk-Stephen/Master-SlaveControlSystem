#include "motors.h"
#include "linesensor.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"
# include <EEPROM.h>

//detect black and white
#define COLORGAP 1500
#define SIDE_COLORGAP 1700

//UPDATE TIME
#define LINE_SENSOR_UPDATE 50
#define KINE_UPDATE 100

Motors_c motors;
LineSensor_c line_sensors;
Kinematics_c kinematics;

bool on_line;                           // on line or not
unsigned long line_sensor_ts, kine_ts;  // time stamp
float sens_val[5];                      // line sensors values
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
  motors.setMotorPower(19 + 8 * w, 19 - 8 * w);
}

bool lineDetected() {
  for (int i = 0; i < 3; i++) {
    if (sens_val[i] > COLORGAP) {
      return true;
    }
  }
  for (int i = 3; i < 5; i++) {
    if (sens_val[i] > SIDE_COLORGAP) {  // 1000
      return true;
    }
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

  on_line = false;
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
  // if ( eeprom_address >= 1020) {
  //   while (1) {
  //     motors.setMotorPower(0.0, 0.0);
  //     //      Serial.println(eeprom_address);
  //   }
  // }

  float elapsed_t;
  unsigned long current_ts;
  current_ts = millis();

  elapsed_t = current_ts - line_sensor_ts;

  if (elapsed_t > LINE_SENSOR_UPDATE) {
    line_sensors.readLineSensor(5, sens_val);
    on_line = lineDetected();
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

  if (on_line == true) {
    weighted(sens_val[0], sens_val[2]);
  } else {
    weighted(sens_val[0], sens_val[2]);
  }

}
