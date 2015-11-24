/*
 * MaxSonar class implementation
 */
#include "maxSonar.h"

// need an array to hold samples we will be reading and sorting
// static keeps them local to this file/library
static const int sonar_arraysize = 9; //quantity of values to find the median (sample size). Needs to be an odd number

// declare the array to store the samples. 
// could perhaps be in class or each instance but this gets into dynamic memory
// and we'd rather keep handle on memory use in microcontroller world
// not necessary to zero the array values here, it just makes the code clearer
static int sonar_rangevalue[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};

//Mode function, returning the mode or median of an integer array of size n
// could be a class function but we're going simple C scope rules here
// and hoping the arduino/library processing respects them
static int sonar_mode(int* x, int n) {
  int i = 0;
  int count = 0;
  int maxCount = 0;
  int mode = 0;
  int bimodal;
  int prevCount = 0;
  while (i < (n - 1)) {
    prevCount = count;
    count = 0;
    while (x[i] == x[i + 1]) {
      count++;
      i++;
    }
    if (count > prevCount && count > maxCount) {
      mode = x[i];
      maxCount = count;
      bimodal = 0;
    }
    if (count == 0) {
      i++;
    }
    if (count == maxCount) { //If the dataset has 2 or more modes.
      bimodal = 1;
    }
    if (mode == 0 || bimodal == 1) { //Return the median if there is no mode.
      mode = x[(n / 2)];
    }
  }
  return mode;
}


MaxSonar::MaxSonar(int pin)
{
  myAnalogPin = pin ;
}

int MaxSonar::readCM(void)
{
  int range;
  for (int i = 0; i < sonar_arraysize; i++)
  {
    range = analogRead(myAnalogPin);  // vcc/1024 is range in 5mm steps
    sonar_rangevalue[i] = (range * 5) / 10 ; // range in cm
    delay(10);
  }
  return sonar_mode(sonar_rangevalue, sonar_arraysize);
}



