#include <Wire.h>
#include <hd44780.h> // main hd44780 header
#include <hd44780_I2Cexp.h> // i2c expander i/o class header
hd44780_I2Cexp lcd; // declare lcd object: auto locate & config exapander chip
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
int sec=0;
int minutes=0;
int hours=0;
int led8=8;
int led9=9;
int pum2=2;
int pum3=3;
bool canstop=1;
bool stopping=0;
ISR(TIMER1_COMPA_vect)
{
  if(stopping==0)
 sec++;
 if (sec >= 60)
 {
 minutes++;
 sec = 0;
 }
 if (minutes >= 60)
 {
 hours++;
 minutes = 0;
 }
}
void setup() {
  int status;
status = lcd.begin(LCD_COLS, LCD_ROWS);
if(status) // non zero status means it was unsuccesful
{
 // begin() failed so blink error code using the onboard LED if possible
 hd44780::fatalError(status); // does not return
}
 noInterrupts(); // disable all interrupts
 // Clear Timer/Counter Control Register for Interrupt 1, bytes A and B (TCCR1?)
 TCCR1A = 0; // Clear TCCR1A/B registers
 TCCR1B = 0;
 TCNT1 = 0; // Initialize counter value to 0 (16-bit counter register)
 // set compare match register for TIMER1: CLOCKFREQUENCY / frequency / prescaler - 1
 OCR1A = 15624; // 16MHz/(1Hz*1024) – 1 (must be <65536)
 // Timer/Counter Control Register for Interrupt 1 on register B
TCCR1B |= (1 << WGM12); // Mode 4, turn on CTC mode
 // Clock Select Bit, Set CS12, CS11 and CS10 bits
 TCCR1B |= (1 << CS12) | (1 << CS10); // Set CS10 and CS12 bits for 1024 prescaler
 TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt , The value in OCR1A is used for compare
 interrupts(); // enable all interrupts
  pinMode(led8,OUTPUT);
  pinMode(led9,OUTPUT);
  pinMode(pum2,INPUT_PULLUP);
  pinMode(pum3,INPUT_PULLUP);
}

void loop() {
  lcd.print(hours);
  lcd.print(":");
  lcd.print(minutes);
  lcd.print(":");
  lcd.print(sec);
  delay(10);
  if (!digitalRead(pum2)&&canstop==1&&stopping==0)
  {
    stopping=1;
    canstop=0;
  }
    if (!digitalRead(pum2)&&canstop==1&&stopping==1)
  {
    stopping=0;
    canstop=0;
  }
  if (digitalRead(pum2))
  {
    canstop=1;
  }
  if (!digitalRead(pum3))
  {
    sec=0;
    minutes=0;
    hours=0;
  }
  lcd.clear();
}
