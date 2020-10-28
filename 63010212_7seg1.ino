int segA = A0;
int segB = A1;
int segC = A2;
int segD = 2;
int segE = 4;
int segF = 7;
int segG = 8;
int segDP = 13;
int seg12 = 5;
void setup()
{
pinMode(segA, OUTPUT);
pinMode(segB, OUTPUT);
pinMode(segC, OUTPUT);
pinMode(segD, OUTPUT);
pinMode(segE, OUTPUT);
pinMode(segF, OUTPUT);
pinMode(segG, OUTPUT);
pinMode(segDP, OUTPUT);
pinMode(seg12, OUTPUT);
}
void loop()
{
displayNumber();
}
void displayNumber()
{
for(int digit = 1 ; digit <= 3 ; digit++)
{
displaySegment(digit); 
delay(500);
}
}
void displaySegment(int numberToDisplay)
{
switch (numberToDisplay)
{
case 1: 
digitalWrite(segA, LOW);
digitalWrite(segB, HIGH);
digitalWrite(segC, HIGH);
digitalWrite(segD, LOW);
digitalWrite(segE, LOW);
digitalWrite(segF, LOW);
digitalWrite(segG, LOW);
digitalWrite(seg12, HIGH);
break;
case 2: 
digitalWrite(segA, HIGH);
digitalWrite(segB, HIGH);
digitalWrite(segC, LOW);
digitalWrite(segD, HIGH);
digitalWrite(segE, HIGH);
digitalWrite(segF, LOW);
digitalWrite(segG, HIGH);
break;
case 3:
digitalWrite(segA, HIGH);
digitalWrite(segB, HIGH);
digitalWrite(segC, HIGH);
digitalWrite(segD, HIGH);
digitalWrite(segE, LOW);
digitalWrite(segF, LOW);
digitalWrite(segG, HIGH);
break;
}
}
