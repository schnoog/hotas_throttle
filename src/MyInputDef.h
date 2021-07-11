#define DEBOUNCE_TIME 5 // ms delay before the push button changes state

// Button
// JOYSTICK 1
//  0 - 12  MCP 1    (frei 13, 14, 15)
// 13 - 16  Analog 2 Digital 
// 17       Analog-Click - bei Modifier
// JOYSTICK 2
// 18 - 31  MCP 2


int LastThrottleReport = 9999;
int axis0 = 0;
int axis1 = 0;
int axis2 = 0;
int axis3 = 0;
int CorrAxis0 = 0;
int CorrAxis1 = 0;

int VirtAxDiff = 400;

int VirtAxModifierButton = 0;
int VirtAxModifiereSuppressButton = 12;
int VirtAxMod_ReplacementKeyVal = 0;
bool VirtAxMod_ReplacementKeyWork = false;
int axis_modifier_overwrite = 512;
bool IsModified = false;


byte switch_state[64];
byte switch_state_old[64];
byte reading, clk, clk_old, realpin, realbutton;
unsigned long debounce_time[64];

void InputDef_Setup(){
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);


    average = 0;
    for (int i=0; i < 10; i++) {
      average = average + analogRead(A0);
    }
    average = average/10;
    CorrAxis0 = 512 - average; 

    average = 0;
    for (int i=0; i < 10; i++) {
      average = average + analogRead(A1);
    }
    average = average/10;
    CorrAxis1 = 512 - average;







}


int debounceVal(int BtnNum, int CurrentVal, int JoyStickNum){
            int FinalBtnNum = 0;
            FinalBtnNum = BtnNum;
            if(JoyStickNum == 2){
                FinalBtnNum = FinalBtnNum - 22;
            }
            reading = (byte)CurrentVal;
            if (reading == switch_state[BtnNum]) debounce_time[BtnNum] = millis() + (unsigned long)DEBOUNCE_TIME;
            else if (millis() > debounce_time[BtnNum]) switch_state[BtnNum] = reading;
            if (switch_state[BtnNum] != switch_state_old[BtnNum]) { // debounced button has changed state
              if (switch_state[BtnNum]) {

                    if(BtnNum == VirtAxModifierButton){
                            IsModified = true;
                    }else{
                        if (BtnNum != VirtAxModifiereSuppressButton){
                            if(JoyStickNum == 1)Joystick.pressButton(FinalBtnNum); 
                            if(JoyStickNum == 2)Joystick2.pressButton(FinalBtnNum); 
                        //    Serial.print(F("Press Button "));
                        //    Serial.print(JoyStickNum);
                        //    Serial.print(" : ");
                        //    Serial.print(BtnNum);
                        //    Serial.print(" - ");
                        //    Serial.println(FinalBtnNum);
                        }else{
                            if(IsModified){
                                VirtAxMod_ReplacementKeyWork = true;
                                VirtAxMod_ReplacementKeyVal = 1;
                            }else{
                                if(JoyStickNum == 1)Joystick.pressButton(FinalBtnNum); 
                                if(JoyStickNum == 2)Joystick2.pressButton(FinalBtnNum); 
                            //    Serial.print(F("Press Button "));
                            //    Serial.println(FinalBtnNum);                                
                            }
                        }
                    }
                }else{
                    if(BtnNum == VirtAxModifierButton){
                            IsModified = false;
                    }else{
                        if (BtnNum != VirtAxModifiereSuppressButton){
                            if(JoyStickNum == 1)Joystick.releaseButton(FinalBtnNum);
                            if(JoyStickNum == 2)Joystick2.releaseButton(FinalBtnNum);
                        //    Serial.print("Release Button ");
                        //    Serial.println(FinalBtnNum);
                        }else{
                            if(IsModified){
                                VirtAxMod_ReplacementKeyWork = true;
                                VirtAxMod_ReplacementKeyVal = 0;
                            }else{
                                if(JoyStickNum == 1)Joystick.releaseButton(FinalBtnNum);
                                if(JoyStickNum == 2)Joystick2.releaseButton(FinalBtnNum);
                            //    Serial.print("Release Button ");
                            //    Serial.println(FinalBtnNum);
                            }
                        }
                    }
                }
              switch_state_old[BtnNum] = switch_state[BtnNum]; // store new state such that the above gets done only once
            }
}


void GetInputs(){
        int Button = 0;

        // MCP 1 Digital Inputs
        //                  0 1 2 3 4 5 6  7  8  9  10  11 12
        int mcp1pins  [] = {14,4,5,6,7,8,9,10,11,13,12,15,0};
        for (int i=0; i<sizeof mcp1pins/sizeof mcp1pins[0]; i++) {           
            int s = mcp1pins[i];
            debounceVal(Button,(int) !mcp1.digitalRead(s),1);
            Button++;
        }
// Todo:Modifier - wenn gedrückt axis0 und 1 auf Mittelstellung (512) setzen
// Analog zu digital wandeln

        // Analog To Digital Trick
        //get Axis Values
        axis0 = analogRead(A0);
        axis1 = analogRead(A1);
        axis0 = axis0 + CorrAxis0;
        axis1 = axis1 + CorrAxis1;
        if (axis0 > 501 && axis0 < 523){axis0 = 512;}
        if (axis1 > 501 && axis1 < 523){axis1 = 512;}


        //axis2 = analogRead(A2);
        //axis3 = analogRead(A3);
        int axis0_A = 0;
        int axis0_B = 0;
        int axis1_A = 0;
        int axis1_B = 0;

        if (IsModified){
            int mmin = 512 - VirtAxDiff;
            int mmax = 512 + VirtAxDiff; 
            if (axis0 > mmax)axis0_A = 1;
            if (axis0 < mmin)axis0_B = 1;
            if (axis1 > mmax)axis1_A = 1;
            if (axis1 < mmin)axis1_B = 1;
            axis2 = axis0;
            axis3 = axis1;
            axis0 = axis_modifier_overwrite;
            axis1 = axis_modifier_overwrite;
        }else{
            axis2 = axis_modifier_overwrite;
            axis3 = axis_modifier_overwrite;

        }

            debounceVal(Button,axis0_A,1);
            Button++;
            debounceVal(Button,axis0_B,1);
            Button++;
            debounceVal(Button,axis1_A,1);
            Button++;
            debounceVal(Button,axis1_B,1);
            Button++;

            axis0_A = 0;
            axis0_B = 0;
            axis1_A = 0;
            axis1_B = 0;

        if (!IsModified){
        int mmin = 513 - VirtAxDiff;
        int mmax = 513 + VirtAxDiff; 
        if (axis0 > mmax)axis0_A = 1;
        if (axis0 < mmin)axis0_B = 1;
        if (axis1 > mmax)axis1_A = 1;
        if (axis1 < mmin)axis1_B = 1;
        }

            debounceVal(Button,axis0_A,1);
            Button++;
            debounceVal(Button,axis0_B,1);
            Button++;
            debounceVal(Button,axis1_A,1);
            Button++;
            debounceVal(Button,axis1_B,1);
            Button++;

        if(VirtAxMod_ReplacementKeyWork){
            if (VirtAxMod_ReplacementKeyVal == 1){
                Joystick.pressButton(Button);
            }else{
                Joystick.releaseButton(Button);
            }
        }
        Button++;
        //einmal durchreichen
        Joystick.setXAxis(axis0);
//        Serial.print(axis0);
//        Serial.print("-");
//        Serial.println(axis1);
        Joystick.setYAxis(axis1);
        Joystick.setRxAxis(axis2);
        Joystick.setRyAxis(axis3);

        // MCP 2 Digital Inputs
        int mcp2pins  [] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        for (int i=0; i<sizeof mcp2pins/sizeof mcp2pins[0]; i++) {           
            int s = mcp2pins[i];
            debounceVal(Button,(int) !mcp2.digitalRead(s),2);
            Button++;
        }

        int mcp3pins  [] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        for (int i=0; i<sizeof mcp3pins/sizeof mcp3pins[0]; i++) {           

            int s = mcp3pins[i];
            if(MCPR2){
                debounceVal(Button,(int) !mcp3.digitalRead(s),2);
            }else{
                debounceVal(Button,(int) !mcp3.digitalRead(s),2);
            }
            Button++;
        }


        // Throttle
        int Throttlevel = GetThrottle();
        Joystick.setThrottle(Throttlevel);        
        //Only reporting changes
        if (Throttlevel != LastThrottleReport){
            //    Serial.print(Throttlevel);
            //    Serial.print(" - ");
            //    Serial.println(average);                
                LastThrottleReport = Throttlevel;
        }



}
