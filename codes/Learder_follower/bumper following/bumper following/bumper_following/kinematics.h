// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _KINEMATICS_H
#define _KINEMATICS_H

#include "math.h"

// Class to track robot position.
class Kinematics_c {
  public:
    float r,l;
    float x,y,theta;
    volatile long count_1, count_0;
    const int countsRerRev = 358.3;
    // Constructor, must exist.
    Kinematics_c() {
      r = 16;//16mm
      l = 42;//48-3.4 mm
      y = 0;
      x = 0;
      theta = 0;
      count_1 = 0;
      count_0 = 0;
    } 

    // Use this function to update
    // your kinematics
    void Update(volatile long count_11, volatile long count_10) {
      float L_WheelSpeed = (2 * M_PI * (count_11 - count_1)) / countsRerRev;
      float R_WheelSpeed = (2 * M_PI * (count_10 - count_0)) / countsRerRev;

      count_1 = count_e1;
      count_0 = count_e0;
      
      float x_before = (r * L_WheelSpeed / 2) + (r * R_WheelSpeed / 2);
      float theta_before = (r * L_WheelSpeed / (2 * l)) - (r * R_WheelSpeed / (2 * l));
      theta_before = theta_before * 180/M_PI;
      x = x + x_before * cos(theta * M_PI/180);
      y = y + x_before * sin(theta * M_PI/180);

      theta = theta + theta_before;
      if(theta > 180){
        theta = theta - 360;
      }
      if(theta <= -180){
        theta = theta + 360;
      }
    }

    float getX(){
      return x;
    }

    float getY(){
      return y;
    }

    float getTheta(){
      return theta;
    }

    
};



#endif
