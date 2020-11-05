#include <Wire.h>
void setup()
{
  Wire.begin(); // Start I2C bus
  Serial.begin(9600); // Setup serial for debug
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop()
{
  byte address, data, device, x;
  for (address = 1; address < 127; address++ ) // sets the value (range from 1 to 127)
  {
    Wire.beginTransmission(address); // transmit to address
    if (Wire.endTransmission() == 0) // I2C devices found
    {
      device = address;
      Serial.print("\n I2C Device Address: "); // Print Device Address
      Serial.println(address, HEX);
      Serial.print("\n");// print as an ASCII-encoded hexa);
    }
  }
  Wire.beginTransmission(device); // transmit to device
  Wire.write(7); // sends one byte 0000 0111
  Wire.endTransmission();

  Wire.requestFrom(device, 1); // recive 1 bytes from slave device
  x = Wire.read(); // Read pin state

  Serial.print("\t pin state : In = "); // Print pin state
  Serial.print(x, BIN); // print as an ASCII-encoded binary);
  x = x & 0x0f;
  if ((x & 4) != 4) {
    Wire.beginTransmission(device); // transmit to device
    Wire.write(16); // sends one byte
    Wire.endTransmission(); // stop transmitting
  }

  else {
    Wire.beginTransmission(device); // transmit to device
    Wire.write(0); // sends one byte
    Wire.endTransmission(); // stop transmitting
  }

}
