
Adafruit_VL53L0X lox = Adafruit_VL53L0X();


const int RunningAverageCount = 3;
float RunningAverageBuffer[RunningAverageCount];
int NextRunningAverage;

int LidarRounds = 10;
int ThrottleMin = 0;
int ThrottleMax = 1023;

int LidarMin = 65;
int LidarMax = 185;

float ThrottleStep;

void Throttle_Setup(){
    Serial.println("Adafruit VL53L0X test");
    if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
    }
    ThrottleStep = (ThrottleMax - ThrottleMin) / (LidarMax - LidarMin);
}

int GetThrottleRaw(){
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
    int average = 0;
    for (int i=0; i < LidarRounds; i++) {
      average = average + measure.RangeMilliMeter;
    }
    average = average/LidarRounds;

    return average;
    //return measure.RangeMilliMeter;
}


int GetThrottleAvg(){
  float RawTemperature = (float)GetThrottleRaw();

  RunningAverageBuffer[NextRunningAverage++] = RawTemperature;
  if (NextRunningAverage >= RunningAverageCount)
  {
    NextRunningAverage = 0; 
  }
  float RunningAverageTemperature = 0;
  for(int i=0; i< RunningAverageCount; ++i)
  {
    RunningAverageTemperature += RunningAverageBuffer[i];
  }
  RunningAverageTemperature /= RunningAverageCount;
  return (int) RunningAverageTemperature;

}

int GetThrottle(){
    int Myval = GetThrottleAvg();
    if (Myval <= LidarMin) return ThrottleMin;
    if (Myval >= LidarMax) return ThrottleMax;
    Myval = Myval - LidarMin;
    float TmpVal = (float) Myval * ThrottleStep;
    return (int) TmpVal;

}