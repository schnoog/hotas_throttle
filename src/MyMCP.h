Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;

const uint8_t addr1 = 0; // Adresse 0x20 / 0
const uint8_t addr2 = 1; // Adresse 0x21 / 1


void MCP_Setup(){
  mcp1.begin(addr1);      // use default address 0
  mcp2.begin(addr2);
    for (int i=0; i < 16; i++) {
          mcp1.pinMode(i, INPUT);
          mcp1.pullUp(i, HIGH);  // turn on a 100K pullup internally
          mcp2.pinMode(i, INPUT);
          mcp2.pullUp(i, HIGH);  // turn on a 100K pullup internally
    }
}

void MCP_Loop(){
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