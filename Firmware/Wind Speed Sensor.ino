// LED +          -> D4
// LED -          -> GND
// LDR pin 1      -> 3.3V
// LDR pin 2      -> A0
// LDR resistor   -> GND

#include <SoftwareSerial.h>
#include "Arduino.h"

int windSpeedLed = 4;
int windSpeedSensor = 0;
int windSpeedSensorMap = 0;
int windSensorStateP = LOW;
int windSensorStateC = LOW;
int windSensorCount = 0;
unsigned long timePrevious = millis();
unsigned long timeCurrent = millis();
unsigned long timeDuration = 3000;

int windCountButtonPower = 6;
int windCountButtonSignal = 2;
int windRotationCount = 0;


void setup() {
  pinMode(windSpeedLed, OUTPUT);
  digitalWrite(windSpeedLed, HIGH);
  pinMode(windSpeedSensor, INPUT);
  pinMode(windCountButtonSignal, INPUT);
  pinMode(windCountButtonPower, OUTPUT);
  digitalWrite(windCountButtonPower, HIGH);
  Serial.begin(9600);
  delay(200);
}

void loop() {
  windSpeedSensor = analogRead(A0);
  windSpeedSensor = map(windSpeedSensor, 230, 410, 0, 100);
//  Serial.println(windSpeedSensor);  //Raw sensor data mapped 0-100

  if (windSpeedSensor > 55) {
    windSensorStateC = HIGH;
    if (windSensorStateP == LOW) {
      windRotationCount++;
    }
  } else {
    windSensorStateC = LOW;
  }
  windSensorStateP = windSensorStateC;

  if (digitalRead(windCountButtonSignal) == HIGH) {
    Serial.println(windRotationCount);
    windRotationCount = 0;
    delay(250);
  }

  //  timeCurrent = millis();
  //  if (timeCurrent - timePrevious > timeDuration) {
  //    Serial.println(windRotationCount);   //Print number of rotations during timeDuration
  //    windRotationCount = 0;
  //    timePrevious = timeCurrent;
  //  }
}
