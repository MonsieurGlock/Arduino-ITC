float sec,minutes,hours;
int temp=0;
bool i=0;
void setup()
{
  Serial.begin(9600);
  noInterrupts(); // disable all interrupts
  // Clear Timer/Counter Control Register for Interrupt 1, bytes A and B (TCCR1?)
  TCCR1A = 0; // Clear TCCR1A/B registers
  TCCR1B = 0;
  TCNT1 = 0; // Initialize counter value to 0 (16-bit counter register)
  // set compare match register for TIMER1: CLOCKFREQUENCY / frequency / prescaler - 1
  OCR1A = 7811; // 16MHz/(1Hz*1024) - 1 (must be <65536)
  // Timer/Counter Control Register for Interrupt 1 on register B
  TCCR1B |= (1 << WGM12); // Mode 4, turn on CTC mode
  // Clock Select Bit, Set CS12, CS11 and CS10 bits
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt , The value in OCR1A is used for compare
  interrupts(); // enable all interrupts
  pinMode(8 , OUTPUT);
  pinMode(9 , OUTPUT);
}
void loop() {
  Serial.print("HOURS : ");
  Serial.print(hours);
  Serial.print(" MIN : ");
  Serial.print(minutes);
  Serial.print(" SEC : ");
  Serial.print(sec);
  Serial.println();
}

ISR(TIMER1_COMPA_vect)
{
  sec += 0.5;
  if(i == 0){
    digitalWrite(8,HIGH);
    }
  if(i == 1){
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    }
  i = !i;
  
  if (sec >= 60)
  {
    digitalWrite(9,HIGH);
    minutes++;
    sec = 0;
  }
  if (minutes >= 60)
  {
    hours++;
    minutes = 0;
  }
}
