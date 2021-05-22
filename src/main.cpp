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
  

  Throttle_Setup();
  MCP_Setup();
}

void loop() {
    LidarDist = GetThrottle();
    Serial.println(LidarDist);
    MCP_Loop();
    
  delay(100);
}