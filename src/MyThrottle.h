#include <HampelFilter.h>

HampelFilter dataBuffer = HampelFilter(0.00, 3, 3.50);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();


int average = 0;
int LidarRounds = 3;
int ThrottleMin = 0;
int ThrottleMax = 1023;

int LidarMin = 60;
int LidarMax = 231;
int LastThrottle;
int MinThrottleSingleStep = 5;

float ThrottleStep;


void Throttle_Setup(){
    //Serial.println("Adafruit VL53L0X test");
    if (!lox.begin()) {
    //Serial.println(F("Failed to boot VL53L0X"));
    while(1);
    }
    //ThrottleStep = (ThrottleMax - ThrottleMin) / (LidarMax - LidarMin);
    lox.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY);    
    ThrottleStep = 5.8181;
    LastThrottle = 9999;
}

int GetThrottleRaw(){
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
    
 //   return (int)measure.RangeMilliMeter;
    
    int mdata;
    average = 0;
    for (int i=0; i < LidarRounds; i++) {
      mdata = (int)measure.RangeMilliMeter;
      dataBuffer.write(mdata);
      average = average + measure.RangeMilliMeter;
    }

    average = average/LidarRounds;
    average = (int)dataBuffer.readMedian();

    //Serial.print("Dist raw value:");
    //Serial.println(average); 
    //return mdata;
    return average;
    //return measure.RangeMilliMeter;
}



int GetThrottle(){
//    int Myval = GetThrottleAvg();
    int Myval = GetThrottleRaw();
    if (Myval <= LidarMin) return ThrottleMin;
    if (Myval >= LidarMax) return ThrottleMax;
    


    Myval = Myval - LidarMin;
    float TmpVal = (float) Myval * ThrottleStep;
    int WorkVal = (int) TmpVal;
    if (WorkVal > LastThrottle + MinThrottleSingleStep) {
        LastThrottle = WorkVal;
        return WorkVal;
    }
    if (WorkVal < LastThrottle - MinThrottleSingleStep) {
        LastThrottle = WorkVal;
        return WorkVal;
    }
    return LastThrottle;
}
