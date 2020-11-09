  
#include <Wire.h>
#include <hd44780.h> // main hd44780 header
#include <hd44780_I2Cexp.h> // i2c expander i/o class header
int i;
hd44780_I2Cexp lcd; // declare lcd object: auto locate & config exapander chip
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

void setup()
{
  Wire.begin(); // Start I2C bus
  Serial.begin(115200); // Setup serial for debug
uint8_t char0[8] = {0x08,0x1C,0x01,0x1A,0x1C,0x0A,0x12,0x0C}; // ชิ
  uint8_t char1[8] = {0x00,0x00,0x1A,0x1A,0x0A,0x0A,0x0F,0x0B}; // น
  uint8_t char2[8] = {0x00,0x00,0x0E,0x11,0x19,0x09,0x09,0x09}; // ก
  uint8_t char3[8] = {0x00,0x0E,0x19,0x09,0x0D,0x0D,0x01,0x01}; // ฤ
  uint8_t char4[8] = {0x00,0x00,0x0A,0x15,0x11,0x15,0x1D,0x11}; // ต
  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status) // non zero status means it was unsuccesful
  {
    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status); // does not return
  }
  //lcd.lineWrap();
  lcd.createChar(0, char0);
  lcd.createChar(1, char1);
  lcd.createChar(2, char2);
  lcd.createChar(3, char3);
  lcd.createChar(4, char4);

  
}
void loop()
{
  byte address, data, device , x;
  byte cat[4];
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
  Serial.print(x, BIN); // print as an ASCII-encoded binary);
  x = x & 0x0f;
  if ((x & 2) == 2 && (x & 1) == 1)
  {
    data = 0x80 | x;
    for (i = 0 ; i < 4; i++) // sets the value (range from 1 to 4)
    {
      Wire.beginTransmission(device); // transmit to device
      Wire.write(data); // sends one byte
      Wire.endTransmission(); // stop transmitting
      delay(10); // wait for stepper speed
      Serial.print("\n Out = "); // Print pin state
      Serial.print(data, BIN); // print as an ASCII-encoded binary);
      cat[i] = data;
      data = data >> 1;
      data = data | x;
      lcd.setCursor(6,0);
      lcd.print("Spin left");
    }
  }

  if ((x & 1) != 1)
  {
    for (i = 3 ; i >= 0; i--) // sets the value (range from 1 to 4)
    {
      Wire.beginTransmission(device); // transmit to device
      Wire.write(cat[i]); // sends one byte
      Wire.endTransmission(); // stop transmitting
      delay(10); // wait for stepper speed
      lcd.setCursor(6,0);
      lcd.print("Spin right");
    }
  }

}
