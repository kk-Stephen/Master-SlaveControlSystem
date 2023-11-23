#include "bumper.h"

#define GAP 1450
#define LOSS 6500
# define MAX_SAMPLES 10
float results[ MAX_SAMPLES ]; // An array of MAX_SAMPLES length

BUMPER_c bumper(GAP，LOSS);

void setup() {

  bumper.initialise();
  Serial.begin(9600);
  delay(1500);
  Serial.println("***RESET***");

} // End of setup()


void loop() {

  
  Serial.print(bumper.readLineSensor(0));
  Serial.print("----");
  Serial.println(bumper.readLineSensor(1));
  Serial.println("----");
  
  

} // End of loop()
