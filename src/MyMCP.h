Adafruit_MCP23017 mcp;


void MCP_Setup(){
  mcp.begin();      // use default address 0
    for (int i=0; i < 16; i++) {
          mcp.pinMode(i, INPUT);
          mcp.pullUp(i, HIGH);  // turn on a 100K pullup internally
    }
}

void MCP_Loop(){
    Serial.print("MCP:");
    for (int i=0; i < 16; i++) {
        Serial.print(mcp.digitalRead(i));
    }
    Serial.println();
}