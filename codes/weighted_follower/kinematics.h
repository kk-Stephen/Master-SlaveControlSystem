// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#include "math.h"
#ifndef _KINEMATICS_H
#define _KINEMATICS_H
#define r 16
#define l 42
#define crp 354.19

float xi;
float yi; 
float theta_i;

// Class to track robot position.
class Kinematics_c {
  long pri_count_e0;
  long pri_count_e1;

  public:
  
    // Constructor, must exist.
    Kinematics_c() {

    } 

    // Use this function to update
    // introduce error:
    // your kinematics
    //r = 16mm
    //CPR = 358.3 = 360 (1 unit = 1 degree)
    //mm of travel per encoder count = 2*pi*r/CRP = 0.279 mm
    //l = (96 mm - 8mm)/2 = 44mm 
    void update() {
      //X r
      float xr = r * M_PI * (( count_e0 - pri_count_e0) + ( count_e1 - pri_count_e1 )) / crp;
      //Theta r
      //float theta_r = r * (( count_e0 - pri_count_e0) - ( count_e1 - pri_count_e1 )) / ( 2 * l );
      float theta_r = r * (( count_e0 - pri_count_e0) - ( count_e1 - pri_count_e1 )) / ( crp * l ) * 180;
      //update position
      xi = xi + ( xr * cos(theta_i * M_PI / 180) );
      yi = yi + ( xr * sin(theta_i * M_PI / 180) );
      theta_i = theta_i - theta_r; //(theta_r * 180 / PI);
      pri_count_e0 = count_e0;
      pri_count_e1 = count_e1;

      //check if theta > 180 or < -180 to prevent theta overflow
      if (theta_i > 180){
        theta_i -= 360;
      }
      if (theta_i<= -180){
        theta_i += 360;
      }
      /*Serial.print("xi: ");
      Serial.print(xi);
      Serial.print("yi: ");
      Serial.println(yi);
      Serial.print("theta: ");
      Serial.print(theta_i);*/
    }
    
    //get delta theta
    float getTheta(){
      return( ( ( count_e0 - pri_count_e0) - ( count_e1 - pri_count_e1 ) ) * r  * 360 / ( 2 * crp * l ) );
    }

};



#endif
