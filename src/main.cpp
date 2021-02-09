#include <Arduino.h>
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool flag = 0;
#include <Servo.h>
int servopin = 9;
int servoSupply = 6;
Servo myservo; // create servo object to control a servo
int timevar;
int potpin = 0; // analog pin used to connect the potentiometer

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(servoSupply, OUTPUT);
  digitalWrite(servoSupply, HIGH);
  myservo.attach(servopin);
  myservo.write(15);
  delay(2000);
  myservo.detach();
#ifndef ESP8266
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB
#endif

  if (!rtc.begin())
  {
    abort();
  }

  if (!rtc.isrunning())
  {
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    delay(3000);
    DateTime now = rtc.now();
    timevar = now.day();
  }

  digitalWrite(servoSupply, LOW);
}

void loop()
{
  delay(3000);
  DateTime now = rtc.now();
  timevar = now.day();
  if (flag == 0 && timevar == 14)
  {
    digitalWrite(servoSupply, HIGH);
    myservo.attach(servopin);
    myservo.write(90);
    delay(1000);
    myservo.detach();
    digitalWrite(servoSupply, LOW);
    flag = 1;
  }
}
