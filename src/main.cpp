#include <Arduino.h>
#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "MyThrottle.h"
#include "MyMCP.h"

#include "MyJoystick.h"
#include "MyInputDef.h" 



int LidarDist;


void setup() {
    Serial.begin(115200);
//  while (! Serial) {
    delay(100);
//  }
  InputDef_Setup();
  Throttle_Setup();
  MCP_Setup();
}

void loop() {
//    LidarDist = GetThrottle();
//    Serial.println(LidarDist);
//    MCP_Loop();
//    Serial.print(analogRead(A0));Serial.print(' ') ; Serial.print(analogRead(A1));Serial.print(' ') ;Serial.print(analogRead(A2));Serial.print(' ') ;Serial.print(analogRead(A3));
//    Serial.println();
  GetInputs();
  Joystick.sendState();
  Joystick2.sendState();
  delay(1);
}