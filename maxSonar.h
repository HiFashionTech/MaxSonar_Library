/*
 * MaxSonar reader
 *    
 */

#ifndef MAXSONAR_H
#define MAXSONAR_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif


class MaxSonar 
{
  public:
    // instance Constructor takes pin for analog reading
    MaxSonar(int pin);

    int readCM(void); // reads sonar N times and returns MODE of the values
  private:
    int myAnalogPin;
    
 };

#endif
