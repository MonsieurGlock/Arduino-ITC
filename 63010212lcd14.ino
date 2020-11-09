#include <Wire.h>
#include <hd44780.h>
#include <hd44780_I2Cexp.h>
hd44780_I2Cexp lcd;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
int col;
int row;
uint8_t char0[8] = {0x01,0x01,0x1A,0x1A,0x09,0x11,0x11,0x0E}; // ช
uint8_t char1[8] = {0x00,0x00,0x0F,0x11,0x11,0x03,0x05,0x02}; // ว
uint8_t char2[8] = {0x00,0x00,0x0E,0x19,0x09,0x09,0x19,0x19}; // ภ
uint8_t char3[8] = {0x00,0x00,0x1D,0x15,0x15,0x15,0x17,0x15}; // ณ

void setup()
{
  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status) // non zero status means it was unsuccesful
  {
    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status); // does not return
  }
  lcd.createChar(0, char0);
  lcd.createChar(1, char1);
  lcd.createChar(2, char2);
  lcd.createChar(3, char3);
}
void loop()
{
  
    lcd.scrollDisplayLeft();
    // wait a bit:
    lcd.setCursor(16,0);
    lcd.write(0); // write character 0
      lcd.write(1); //
      lcd.write(2); // write character 2
      lcd.write(3); // write character 3
    delay(200);
  
}
      
      
