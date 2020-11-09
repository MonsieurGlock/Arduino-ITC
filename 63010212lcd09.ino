#include <Wire.h>
#include <hd44780.h>
#include <hd44780_I2Cexp.h>
hd44780_I2Cexp lcd;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
int col;
int row;
void setup()
{
  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status) // non zero status means it was unsuccesful
  {
    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status); // does not return
  }
}
void loop()
{
  lcd.cursor(); // turn on cursor so you can see where it is row = 0;
  col = 0;
  for (int i = 0; i < 256; i++) // start at the character for the number zero
  {
    lcd.setCursor(col, row);
    lcd.print(char(i)); // print ASCII chars
    col = col + 1;
    if (col == 16)
    {
      col = 0;
      row = row + 1;
      if (row == 2)
        row = 0;
    }
    delay(50); // slow things down to watch the printing & wrapping
  }
  delay(2000);
}
