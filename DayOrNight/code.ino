/*
Project: Servo motor + light sensor to detect if day or night
Author: zubest
Date: July 15th 2020
*/

#include <Servo.h>

Servo s;
int angle;
const int lightSensorPin = A0;
int lightSensorValue = 0;
int lightValue = 0;
const int day = 255;
const int night = 83;
void setup(){
  s.attach(9);
  Serial.begin(9600);
}

void loop(){
  lightSensorValue = analogRead(lightSensorPin);
  Serial.print("Raw Sensor Value: ");
  Serial.print(lightSensorValue);
  // de 1023 a 255
  lightValue = lightSensorValue/4;
  Serial.println("Sensor Value: ");
  Serial.print(lightValue);
  angle = map(lightValue, 0, 255, 0, 179);
  if(lightValue <= day && lightValue > night){
    angle = 80;
  }else if (lightValue <= night){
    angle = 150;
    }
  Serial.println("Angle: ");
  Serial.print(angle);
  s.write(angle);
  delay(150);
}
