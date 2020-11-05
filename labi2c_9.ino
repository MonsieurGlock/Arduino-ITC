#include <Wire.h>
int x;
void setup()
{
  Wire.begin(); // Start I2C bus
  Serial.begin(9600); // Setup serial for debug
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop()
{
  byte address, data, device;
  for (address = 1; address < 127; address++ ) // sets the value (range from 1 to 127)
  {
    Wire.beginTransmission(address); // transmit to address
    if (Wire.endTransmission() == 0) // I2C devices found
    {
      device = address;
     // Serial.print("\n I2C Device Address: "); // Print Device Address
     // Serial.println(address, HEX); // print as an ASCII-encoded hexa);
    }
    
  }
   
  Wire.requestFrom(device, 1); // recive 1 bytes from slave device
  x = Wire.read(); // Read pin state
  Serial.println("\t pin state : In = "); // Print pin state
  Serial.print(x,BIN); // print as an ASCII-encoded binary);
  x = x & 0x0f;
  Serial.print(x);
  if (x == 3)
  {
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on
  }
  else{
    digitalWrite(LED_BUILTIN, LOW); // turn the LED off
  }
}
