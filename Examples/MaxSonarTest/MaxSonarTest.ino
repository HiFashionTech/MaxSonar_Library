/*  
  MaxSonar Library Test
*/

#include "maxSonar.h"

//////////////////////////////////////////
// Create a MaxSonar instance, with the pin number to recieve the signal.
MaxSonar sonar = MaxSonar(0);

void setup() {

  //Open up a serial connection
  Serial.begin(115200);
  //Wait for the serial connection
  delay(500);
  Serial.println("Maxbotix Sonar test");
  
  int range = sonar.readCM();
  int zone = findZone(range);
  Serial.print("Range CM is: "); Serial.print(range);
  Serial.print(" Zone is: "); Serial.print(zone);
  Serial.println();
  
  
}

//Main loop where the action takes place
void loop() {
  // read the sonar in centimeters (median of N reads)
  int range = sonar.readCM();
  // process raw distance into one of several 'zones' (see below)
  // lowest number is nearest
  int zone = findZone(range);
  
  // report to serial terminal
  Serial.print("Range CM is: "); Serial.print(range);
  Serial.print(" Zone is: "); Serial.print(zone);
  Serial.println();

  // wait a little while
  delay(100);
}


// Define several Zones  lowest number is nearest
const int zoneO = 30;
const int zone1 = 121;// 4ft
const int zone2 = 243;
const int zone3 = 365;
const int zone4 = 10000;

int findZone(long range)
{
  if (range <= zoneO)
    return 0;
  if (range <= zone1)
    return 1;
  if (range <= zone2)
    return 2;
  if (range <= zone3)
    return 3;
  return 4;
}

