void setup() {
  Serial.begin(9600);        // Initialize Serial communication for Serial Port 0
  Serial3.begin(4800);       // Initialize Serial communication for Serial Port 3, tried 9600 also
  delay(100);                // Wait for the Serial ports to initialize
}

void loop() {
  // Set the output voltage using Serial Port 3
  setOutputVoltage(1234);    // Set the voltage to 12.34V (example value)
  
  // Read the actual output voltage using Serial Port 3
  float voltage = readOutputVoltage();
  
  // Print the voltage value to Serial Port 0
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");
  
  delay(1000);               // Delay before repeating the loop
}

void setOutputVoltage(uint16_t voltage) {
  char command[10];
  sprintf(command, "awu%04d\r\n", voltage);  // Format the command string
  
  Serial3.print(command);    // Send the command to set the output voltage
}

float readOutputVoltage() {
  Serial3.println("aru");    // Send the command to read the output voltage
  
  // Wait for the response
  delay(100);                  
  
  // Read the response from Serial Port 3
  if (Serial3.available()) {
    String response = Serial3.readStringUntil('\n');
    
    // Extract the voltage value from the response
    if (response.startsWith("#ru")) {
      String voltageStr = response.substring(5);
      float voltage = voltageStr.toFloat();
      return voltage;
    }
    else {
      return 6.9;
      }
  }
  
  return 0.0;   // Return 0.0 if there was an error or no response received
}
