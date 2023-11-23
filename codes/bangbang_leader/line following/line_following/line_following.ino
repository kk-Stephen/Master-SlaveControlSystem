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
  // put your main code here, to run repeatedly:
  LineFollowing();
  //motors.setMotorPower(-30, 30);
}

void LineFollowing() {
  if ( linesensor.lineDetected() ) {
    int BiasPWM = 20;
    int MaxTurnPWM = 40;
    float W;
    W = linesensor.weightedMesurement();
    int LeftPWM = BiasPWM - (W * MaxTurnPWM);
    int RightPWM = BiasPWM + (W * MaxTurnPWM);
    motors.setMotorPower(LeftPWM, RightPWM);
  }
  else {
    //可能要再往前走一小点点来判断
    //motors.setMotorPower(50.0, 50.0);
    //delay(75);
    unsigned long findingLine = millis();
    if (linesensor.readLineSensor(1) >= GAP && linesensor.readLineSensor(3) >= GAP && linesensor.readLineSensor(0) < GAP && linesensor.readLineSensor(4) < GAP) {
      while(true){
        motors.setMotorPower(0.0, 0.0);
      delay(3000);
      
      }
      return;
    }

    //非解密
    else {
      while (linesensor.readLineSensor(0) < GAP  && linesensor.readLineSensor(4) < GAP) {
        unsigned long currentTime = millis();
        if (currentTime - findingLine > 500) {
          break;
        }
        motors.setMotorPower(20.0, 20.0);
      }

      if (linesensor.readLineSensor(0) < GAP && linesensor.readLineSensor(4) < GAP) {
        //原地转90度返回???????有问题，建议设计时间戳来检测是否到尽头了，还得检测是1开始的时候还是2结束的时候还是3路程中的时候
        while (!linesensor.lineDetected()) {
          motors.setMotorPower(-20.0, 20.0);/////////////
        }
      }
      if (linesensor.readLineSensor(0) >= GAP && linesensor.readLineSensor(4) < GAP) {
        //左转90度
        while (!linesensor.lineDetected()) {
          motors.setMotorPower(1.0, 20.0);
        }
      }
      if (linesensor.readLineSensor(4) >= GAP && linesensor.readLineSensor(0) < GAP) {
        //右转90度
        while (!linesensor.lineDetected()) {
          motors.setMotorPower(20.0, 1.0);
        }
      }
    }
  }
}//////////////////////
