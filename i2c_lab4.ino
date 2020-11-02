#include <Wire.h>
void setup()
{
  Wire.begin(); // Start I2C bus
  Serial.begin(9600); // Setup serial for debug
  
}
int x;
void loop()
{
  byte address, data, device;
  for (address = 1; address < 127; address++ ) // sets the value (range from 1 to 127)
  {
    Wire.beginTransmission(address); // transmit to address
    if (Wire.endTransmission() == 0) // I2C devices found
    {
      device = address;

    }
  }
  for (data = 0 ; data <= 255; data++) // sets the value (range from 0 to 255)
  {
    Wire.beginTransmission(device); // transmit to device
    Wire.write(data); // sends one byte
    Wire.endTransmission(); // stop transmitting
    Serial.print("pin state : Out = "); // Print pin state
    Serial.println(data, BIN); // print as an ASCII-encoded binary);
    delay(100);
  }
}
