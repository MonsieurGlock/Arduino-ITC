//declare variables for the motor pins
int motorPin1 = 8;
int motorPin2 = 9;
int motorPin3 = 10;
int motorPin4 = 11;
int motorSpeed = 5;
int stepCount = 0;
void setup()
{
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  //wavedrive();
   //fullstep();
  halfstep();

  Serial.print("steps:" );
  Serial.println(stepCount);
  stepCount++;
}
void halfstep()
{
// 1
digitalWrite(motorPin4, HIGH);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin1, LOW);
delay(motorSpeed);
// 2
digitalWrite(motorPin4, HIGH);
digitalWrite(motorPin3, HIGH);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin1, LOW);
delay (motorSpeed);
// 3
digitalWrite(motorPin4, LOW);
digitalWrite(motorPin3, HIGH);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin1, LOW);
delay(motorSpeed);
// 4
digitalWrite(motorPin4, LOW);
digitalWrite(motorPin3, HIGH);
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin1, LOW);
delay(motorSpeed);
// 5
digitalWrite(motorPin4, LOW);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin1, LOW);
delay(motorSpeed);
// 6
digitalWrite(motorPin4, LOW);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin1, HIGH);
delay (motorSpeed);
// 7
digitalWrite(motorPin4, LOW);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin1, HIGH);
delay(motorSpeed);
// 8
digitalWrite(motorPin4, HIGH);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin1, HIGH);
delay(motorSpeed);
}
