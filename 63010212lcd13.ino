#include <Wire.h>
#include <hd44780.h>
#include <hd44780_I2Cexp.h>
hd44780_I2Cexp lcd;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
int col;
int row;
uint8_t char0[8] = {0x00, 0x00, 0x03, 0x04, 0x08, 0x19, 0x11, 0x10}; // Char 0 - Upper-left
uint8_t char1[8] = {0x00, 0x1F, 0x00, 0x00, 0x00, 0x11, 0x11, 0x00}; // Char 1 - Upper-middle
uint8_t char2[8] = {0x00, 0x00, 0x18, 0x04, 0x02, 0x13, 0x11, 0x01}; // Char 2 - Upper-right
uint8_t char3[8] = {0x12, 0x13, 0x1b, 0x09, 0x04, 0x03, 0x00, 0x00}; // Char 3 - Lower-left
uint8_t char4[8] = {0x00, 0x11, 0x1f, 0x1f, 0x0e, 0x00, 0x1F, 0x00}; // Char 4 - Lower-middle
uint8_t char5[8] = {0x09, 0x19, 0x1b, 0x12, 0x04, 0x18, 0x00, 0x00}; // Char 5 - Lower-right
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
  lcd.createChar(4, char4);
  lcd.createChar(5, char5);
}
void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(0); // write character 0
  lcd.write(1); //
  lcd.write(2); // write character 2
  lcd.setCursor(0, 1);
  lcd.write(3); // write character 3
  lcd.write(4); // write character 4
  lcd.write(5); // write character 5
  delay(2000);
}
