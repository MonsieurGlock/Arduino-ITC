#include <Wire.h>
#include <hd44780.h>
#include <hd44780_I2Cexp.h>
hd44780_I2Cexp lcd;

long double t1, t2, t11, t22;
float sec = 0.0;
int minutes = 0;
int hours = 0;
bool check = false;
bool pressed = false;

const int LCD_COLS = 16;
const int LCD_ROWS = 2;

byte address,data,device1,device2,x;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  t1 = millis();
  t2 = millis();
  int count1 = 0;
  for(address = 1; address < 127; address++ ) // sets the value (range from 1 to 127)
  {
    Wire.beginTransmission(address); // transmit to address
    if (Wire.endTransmission() == 0) // I2C devices found
    {
      if(count1 == 0)
      {
        device1 = address;    
        Serial.print("\n I2C Device Address1: "); // Print Device Address
        Serial.println(address, HEX); // print as an ASCII-encoded hexa);
        count1++;
      }
      else if(count1 == 1)
      {
        device2 = address;    
        Serial.print("\n I2C Device Address2: "); // Print Device Address
        Serial.println(address, HEX); // print as an ASCII-encoded hexa);
      }
    }
  }

  lcd.begin(0, 0);
  lcd.setCursor(0, 1);

  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3) ,reset , CHANGE);
  attachInterrupt(digitalPinToInterrupt(2) ,count , CHANGE);
  noInterrupts(); // disable all interrupts
  // Clear Timer/Counter Control Register for Interrupt 1, bytes A and B (TCCR1?)
  TCCR1A = 0; // Clear TCCR1A/B registers
  TCCR1B = 0;
  TCNT1 = 0; // Initialize counter value to 0 (16-bit counter register)
  // set compare match register for TIMER1: CLOCKFREQUENCY / frequency / prescaler - 1
  OCR1A = 7811.5; // 16MHz/(2Hz*1024) – 1 (must be <65536)
  // Timer/Counter Control Register for Interrupt 1 on register B
  TCCR1B |= (1 << WGM12); // Mode 4, turn on CTC mode
  // Clock Select Bit, Set CS12, CS11 and CS10 bits
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set CS10 and CS12 bits for 1024 prescaler
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt , The value in OCR1A is used for compare
  interrupts(); // enable all interrupts
    
}

void loop() {
  Serial.print("Hours : ");
  Serial.print(hours);
  Serial.print(" Minutes : ");
  Serial.print(minutes);
  Serial.print(" Seconds : ");
  Serial.println(int (sec));
  Serial.println(digitalRead(5));

  if(millis() - t1 >= 1000)
  {
    t1 = millis();
    t11 = millis();
    render();
  }
  motor();
  if(millis() - t11 >= 920)
  {
    lcd.clear();
  }
}

void count()
{
  if(digitalRead(2) == LOW)
    pressed = !pressed;
}

void reset()
{
  if(digitalRead(3) == LOW)
    {
      hours = 0;
      minutes = 0;
      sec = 0.0;
    }
}

ISR(TIMER1_COMPA_vect)
{
  if(pressed)
    {
      sec += 0.5;
      if(check==true)
      {
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);   
      }
      else
      {
        digitalWrite(8, LOW);
      }
      check = !check;
      if (sec >= 60.0)
      {
        digitalWrite(9, HIGH);
        minutes++;
        sec = 0.0;
      }
      if (minutes >= 60)
      {
        hours++;
        minutes = 0;
      }
    }
}

void render()
{
  lcd.print(hours); lcd.print(":");
  lcd.print(minutes); lcd.print(":");
  lcd.print(int(sec));
}

void motor()
{
  data = 0x80; //1000 0000 --> 0100 0000
  for (int i = 1 ; i <= 4; i++) // sets the value (range from 1 to 8)
  {
    Wire.beginTransmission(device2); // transmit to device
    Wire.write(data); // sends one byte
    Wire.endTransmission(); // stop transmitting
    Serial.print("pin state : Out = "); // Print pin state
    Serial.print(data, BIN); // print as an ASCII-encoded binary);
    delay(5); // wait for stepper speed
    data = data >> 1;
    Wire.requestFrom(device2, 1); // receive 1 bytes from slave device
    x = Wire.read(); // Read pin state
    Serial.print("\t, In = "); // Print pin state
    Serial.println(x, BIN); // print as an ASCII-encoded binary);
  }
}
