#include "Joystick.h"


  //                      hidReportId
Joystick_ Joystick(0x03,
  //  joystickType          buttonCount   hatSwitchCount  
  JOYSTICK_TYPE_JOYSTICK,     22,            0,
  //includeXAxis includeYAxis includeZAxis includeRxAxis includeRyAxis includeRzAxis
       true,         true,       false,       false,        false,        false,
  //includeRudder  includeThrottle includeAccelerator includeBrake includeSteering
       true,           true,            false,            false,       false);

Joystick_ Joystick2(0x04,
  //  joystickType          buttonCount   hatSwitchCount  
  JOYSTICK_TYPE_JOYSTICK,     32,            0,
  //includeXAxis includeYAxis includeZAxis includeRxAxis includeRyAxis includeRzAxis
       false,         false,       false,       false,        false,        false,
  //includeRudder  includeThrottle includeAccelerator includeBrake includeSteering
       false,           false,            false,            false,       false);

//uint8_t hidReportId - Default: 0x03 - Indicates the joystick's HID report ID. This value must be unique if you are creating multiple instances of Joystick. Do not use 0x01 or 0x02 as they are used by the built-in Arduino Keyboard and Mouse libraries.
//uint8_t joystickType - Default: JOYSTICK_TYPE_JOYSTICK or 0x04 - Indicates the HID input device type. Supported values:
//  JOYSTICK_TYPE_JOYSTICK or 0x04 - Joystick
//  JOYSTICK_TYPE_GAMEPAD or 0x05 - Gamepad
//  JOYSTICK_TYPE_MULTI_AXIS or 0x08 - Multi-axis Controller
//uint8_t buttonCount - Default: 32 - Indicates how many buttons will be available on the joystick.
//uint8_t hatSwitchCount - Default: 2 - Indicates how many hat switches will be available on the joystick. Range: 0 - 2
//bool includeXAxis - Default: true - Indicates if the X Axis is available on the joystick.
//bool includeYAxis - Default: true - Indicates if the Y Axis is available on the joystick.
//bool includeZAxis - Default: true - Indicates if the Z Axis (in some situations this is the right X Axis) is available on the joystick.
//bool includeRxAxis - Default: true - Indicates if the X Axis Rotation (in some situations this is the right Y Axis) is available on the joystick.
//bool includeRyAxis - Default: true - Indicates if the Y Axis Rotation is available on the joystick.
//bool includeRzAxis - Default: true - Indicates if the Z Axis Rotation is available on the joystick.
//bool includeRudder - Default: true - Indicates if the Rudder is available on the joystick.
//bool includeThrottle - Default: true - Indicates if the Throttle is available on the joystick.
//bool includeAccelerator - Default: true - Indicates if the Accelerator is available on the joystick.
//bool includeBrake - Default: true - Indicates if the Brake is available on the joystick.
//bool includeSteering - Default: true - Indicates if the Steering is available on the joystick.


void Joystick_Setup(){
    Joystick.setXAxisRange(4, 1019);
    Joystick.setYAxisRange(4, 1019);
    Joystick.setThrottleRange(0,1023);



}