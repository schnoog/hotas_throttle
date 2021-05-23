#include <Arduino.h>
#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "MyThrottle.h"
#include "MyMCP.h"

int LidarDist;

void setup() {
    Serial.begin(115200);
  while (! Serial) {
    delay(1);
  }
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);

  Throttle_Setup();
  MCP_Setup();
}

void loop() {
    LidarDist = GetThrottle();
    Serial.println(LidarDist);
    MCP_Loop();
    Serial.print(analogRead(A0));Serial.print(' ') ; Serial.print(analogRead(A1));Serial.print(' ') ;Serial.print(analogRead(A2));Serial.print(' ') ;Serial.print(analogRead(A3));
    Serial.println();
  delay(100);
}