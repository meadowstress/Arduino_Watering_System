// Configuration tool for real time clock
// do not configure the external clock in your sketch but use this code to
// set the proper time for once

//www.elegoo.com
//2018.10.24
#include <Wire.h>
#include <DS3231.h>

DS3231 clock_var;
RTCDateTime DateTime;

void setup()
{
  Serial.begin(9600);

  Serial.println("Initialize DS3231");
  // Initialize the DS3231 object
  clock_var.begin();

  // 1st step: set time
  // Enable the clock.setDateTime function for the first run and flash the
  // the code on the hardware so that the time of the clock is beeing set

  // 2nd step: disable setting time
  // IMPORTANT: Then comment out the function again and flash it again.

  // 3rd step: test
  // NOW you can check if the clock runs while disconnecting the Arduino
  // from the power supply after reconnecting the arduino you can check in the
  // serial monitor if the time has been continuing

  // Manual (YYYY, MM, DD, HH, II, SS
  // clock_var.setDateTime(2020, 4, 9, 8, 31, 45);
}

void loop()
{
  DateTime = clock_var.getDateTime();

  // For leading zero look to DS3231_dateformat example

  Serial.print("Raw data: ");
  Serial.print(DateTime.year);
  Serial.print("-");
  Serial.print(DateTime.month);
  Serial.print("-");
  Serial.print(DateTime.day);
  Serial.print(" ");
  Serial.print(DateTime.hour);
  Serial.print(":");
  Serial.print(DateTime.minute);
  Serial.print(":");
  Serial.print(DateTime.second);
  Serial.println("");

  delay(1000);
}
