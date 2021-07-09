Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp3;


const uint8_t addr1 = 0; // Adresse 0x20 / 0
const uint8_t addr2 = 1; // Adresse 0x21 / 1
const uint8_t addr3 = 2; // Adresse 0x22 / 2

bool MCPR0 = false;
bool MCPR1 = false;
bool MCPR2 = false;

boolean  MCP_READY(int MCP_Num){
    return true;
    uint8_t add;
    byte error;


    if (MCP_Num == 0) add = addr1;
    if (MCP_Num == 1) add = addr2;
    if (MCP_Num == 2) add = addr3;
    Wire.begin();
    Wire.beginTransmission(add);
    error = Wire.endTransmission();
    if (error == 0) {
        Serial.print("MCP ");
        Serial.print(MCP_Num);
        Serial.println(" ready");
        return true;
    }
        Serial.print("MCP ");
        Serial.print(MCP_Num);
        Serial.println(" missing");
    return false;

}


void MCP_Setup(){
    delay(10000);
    MCPR0 = MCP_READY(0);
    MCPR1 = MCP_READY(1);
    MCPR2 = MCP_READY(2);

  mcp1.begin(addr1);      // use default address 0
  mcp2.begin(addr2);
  if(MCPR2)mcp3.begin(addr3);
    for (int i=0; i < 16; i++) {
          mcp1.pinMode(i, INPUT);
          mcp1.pullUp(i, HIGH);  // turn on a 100K pullup internally
          mcp2.pinMode(i, INPUT);
          mcp2.pullUp(i, HIGH);  // turn on a 100K pullup internally
          if(MCPR2)mcp3.pinMode(i, INPUT);
          if(MCPR2)mcp3.pullUp(i, HIGH);
    }
}

void MCP_LoopA(){
    Serial.print("MCP1:");
    for (int i=0; i < 16; i++) {
        Serial.print(mcp1.digitalRead(i));
    }
    Serial.println();
    Serial.print("MCP2:");
    for (int i=0; i < 16; i++) {
        Serial.print(mcp2.digitalRead(i));
    }
    Serial.println();
}

void MCP_Loop(){
    for (int i=0; i < 16; i++) {
        if ((int)mcp1.digitalRead(i) == (int)0){
            Serial.println(i);
        }
    }

}