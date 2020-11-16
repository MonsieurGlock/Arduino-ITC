int sec;
int minutes;
int hours;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  noInterrupts(); // disable all interrupts
  // Clear Timer/Counter Control Register for Interrupt 1, bytes A and B (TCCR1?)
  TCCR1A = 0; // Clear TCCR1A/B registers
  TCCR1B = 0;
  TCNT1 = 0; // Initialize counter value to 0 (16-bit counter register)
  // set compare match register for TIMER1: CLOCKFREQUENCY / frequency / prescaler - 1
  OCR1A = 15624; // 16MHz/(1Hz*256) - 1 (must be <65536)
  // Timer/Counter Control Register for Interrupt 1 on register B
  TCCR1B |= (1 << WGM12); // Mode 4, turn on CTC mode
  // Clock Select Bit, Set CS12, CS11 and CS10 bits
  TCCR1B |= (1 << CS12)|(1<<CS10); // Set CS12 bit for 256 prescaler
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt , The value in OCR1A is used for compare
  interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(" ");
  Serial.print(hours);
  Serial.print(" ");
  Serial.print(minutes);
  Serial.print(" ");
  Serial.println(sec );
}

ISR(TIMER1_COMPA_vect)
{
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
