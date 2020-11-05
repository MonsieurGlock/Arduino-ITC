#include <Wire.h>
int i;
void setup()
{
  Wire.begin(); // Start I2C bus
  Serial.begin(115200); // Setup serial for debug
}
void loop()
{
  byte address, data, device , x, temp;
  byte cat[4];
  byte spider[8] = {135 , 199 , 103, 71 , 39 , 47 , 23 , 31};
  for (address = 1; address < 127; address++ ) // sets the value (range from 1 to 127)
  {
    Wire.beginTransmission(address); // transmit to address
    if (Wire.endTransmission() == 0) // I2C devices found
    {
      device = address;
      //Serial.print("\n I2C Device Address: "); // Print Device Address
      //Serial.println(address, HEX); // print as an ASCII-encoded hexa);
    }
  }
  Wire.requestFrom(device, 1); // recive 1 bytes from slave device


  x = Wire.read(); // Read pin state
  Serial.print("\t pin state : In = "); // Print pin state
  Serial.println(x, BIN); // print as an ASCII-encoded binary);
  x = x & 0x0f;
  if ((x & 2) == 2 && (x & 1) == 1)
  {
    data = 0x80 | x;
    for (i = 0 ; i < 4; i++) // sets the value (range from 1 to 4)
    {

      Wire.beginTransmission(device); // transmit to device
      Wire.write(data); // sends one byte
      Wire.endTransmission(); // stop transmitting
      delay(5); // wait for stepper speed
      //Serial.print("\n Out = "); // Print pin state
      Serial.println(data, BIN); // print as an ASCII-encoded binary);
      cat[i] = data;
      data = data >> 1;
      data = data | x;
      temp = data ;
      data = data | cat[i];
      Wire.beginTransmission(device); // transmit to device
      Wire.write(data); // sends one byte
      Wire.endTransmission();
      Serial.println(data, BIN);
      data = temp ;
    }
  }

  if ((x & 1) != 1)
  {
    for (i = 7 ; i >= 0; i--) // sets the value (range from 1 to 4)
    {
      Wire.beginTransmission(device); // transmit to device
      Wire.write(spider[i]); // sends one byte
      Wire.endTransmission(); // stop transmitting
      delay(5); // wait for stepper speed
      Serial.println(spider[i], BIN);

    }
  }
}
