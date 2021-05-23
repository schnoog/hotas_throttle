#define DEBOUNCE_TIME 5 // ms delay before the push button changes state

int LastThrottleReport = 9999;
int axis0 = 0;
int axis1 = 0;
int axis2 = 0;
int axis3 = 0;

int VirtAxDiff = 400;
byte switch_state[32];
byte switch_state_old[32];
byte reading, clk, clk_old, realpin, realbutton;
unsigned long debounce_time[32];

void InputDef_Setup(){
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
}


int debounceVal(int BtnNum, int CurrentVal){

            reading = (byte)CurrentVal;
            if (reading == switch_state[BtnNum]) debounce_time[BtnNum] = millis() + (unsigned long)DEBOUNCE_TIME;
            else if (millis() > debounce_time[BtnNum]) switch_state[BtnNum] = reading;
            if (switch_state[BtnNum] != switch_state_old[BtnNum]) { // debounced button has changed state
              if (switch_state[BtnNum]) {
                    Joystick.pressButton(BtnNum); 
                    Serial.print("Press Button ");
                    Serial.println(BtnNum);

                }else{
                    Joystick.releaseButton(BtnNum);
                    Serial.print("Release Button ");
                    Serial.println(BtnNum);
                }



              switch_state_old[BtnNum] = switch_state[BtnNum]; // store new state such that the above gets done only once
            }
}


void GetInputs(){
        int Button = 0;

        // MCP 1 Digital Inputs
        int mcp1pins  [] = {0,4,5,6,7,8,9,10,11,12,13,14,15};
        for (int i=0; i<sizeof mcp1pins/sizeof mcp1pins[0]; i++) {           
            int s = mcp1pins[i];
            debounceVal(Button,(int) !mcp1.digitalRead(s));
            Button++;
        }

        // Analog To Digital Trick
        //get Axis Values
        axis0 = analogRead(A0);
        axis1 = analogRead(A1);
        axis2 = analogRead(A2);
        axis3 = analogRead(A3);
        //einmal durchreichen
        Joystick.setXAxis(axis0);
        Joystick.setYAxis(axis1);

        int axis0_A = 0;
        int axis0_B = 0;
        int axis1_A = 0;
        int axis1_B = 0;
        int mmin = 513 - VirtAxDiff;
        int mmax = 513 + VirtAxDiff; 
        if (axis0 > mmax)axis0_A = 1;
        if (axis0 < mmin)axis0_B = 1;
        if (axis1 > mmax)axis1_A = 1;
        if (axis1 < mmin)axis1_B = 1;

        debounceVal(Button,axis0_A);
        Button++;
        debounceVal(Button,axis0_B);
        Button++;
        debounceVal(Button,axis1_A);
        Button++;
        debounceVal(Button,axis1_B);
        Button++;

        // MCP 2 Digital Inputs
        int mcp2pins  [] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        for (int i=0; i<sizeof mcp2pins/sizeof mcp2pins[0]; i++) {           
            int s = mcp2pins[i];
            debounceVal(Button,(int) !mcp2.digitalRead(s));
            Button++;
        }



        // Throttle
        int Throttlevel = GetThrottle();
        Joystick.setThrottle(Throttlevel);        
        //Only reporting changes
        if (Throttlevel != LastThrottleReport){
                Serial.print("New throttle val: ");
                Serial.println(Throttlevel);
                LastThrottleReport = Throttlevel;
        }



}
