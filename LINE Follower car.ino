//Right motors declaration
#define Motor1_Forward  13
#define Motor1_Backward 12
#define ENL 11

//Left motors declaration
#define Motor2_Forward  4
#define Motor2_Backward 3
#define ENR 10
//Line tracker declaration
#define R 7
#define C 8
#define L 9

//Ultrasonic declration
#define Triger 6
#define Echo   5

//Variables declaration
int Counter = 1;

//Functions

void Forward() //Function to move forward
{
digitalWrite(Motor1_Forward,HIGH);
digitalWrite(Motor1_Backward,LOW);
digitalWrite(Motor2_Forward,HIGH);
digitalWrite(Motor2_Backward,LOW);
analogWrite(ENR,64);
analogWrite(ENR,64);
}

void Turn180() //Function to turn around 180 degrees
{
digitalWrite(Motor1_Forward ,HIGH);
digitalWrite(Motor1_Backward, LOW);
digitalWrite(Motor2_Forward , LOW);
digitalWrite(Motor2_Backward,HIGH);
analogWrite(ENL,128);
analogWrite(ENR,128);
delay(800);
}

void Stop() //Function to stop
{
digitalWrite(Motor1_Forward ,LOW);
digitalWrite(Motor1_Backward,LOW);
digitalWrite(Motor2_Forward ,LOW);
digitalWrite(Motor2_Backward,LOW);
}

void Left() //Function to go left
{
digitalWrite(Motor1_Forward,LOW);
digitalWrite(Motor1_Backward,HIGH);
digitalWrite(Motor2_Forward,HIGH);
digitalWrite(Motor2_Backward,LOW);
analogWrite(ENR,180);
analogWrite(ENL,90);
}

void Right() //Function to go right
{
digitalWrite(Motor1_Forward,HIGH);
digitalWrite(Motor1_Backward,LOW);
digitalWrite(Motor2_Forward,LOW);
digitalWrite(Motor2_Backward,HIGH);
analogWrite(ENL,180);
analogWrite(ENR,90);
}

double US_Measure() {
  digitalWrite(Triger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Triger, LOW);
  
  double dist = pulseIn(Echo, HIGH) * 0.034 / 2;
  Serial.print("Dist ");
  Serial.print(": ");
  Serial.print(dist);
  Serial.println(" cm");
  return dist;
}

void setup()
{  Serial.begin(9600);
  Serial.println("Started!");

  //Motor pins
pinMode(Motor1_Forward ,OUTPUT);
pinMode(Motor1_Backward,OUTPUT);
pinMode(Motor2_Forward ,OUTPUT);
pinMode(Motor2_Backward,OUTPUT);

  //IR sensor pins
pinMode(C,INPUT);
pinMode(R,INPUT);
pinMode(L,INPUT);

  //Ultrasonic pins
pinMode(Triger,OUTPUT);
pinMode(Echo  ,INPUT);

}

void loop()
{
int Dist ; 

int c =digitalRead(C);
int r =digitalRead(R);
int l =digitalRead(L);

Dist = US_Measure(); //Condition to check for obstical
if(Dist < 5);
{
Stop();
while(Dist < 5)
{
  Dist = US_Measure();
}
}

if (l == LOW && r == LOW && c == HIGH) //Condition to move forward
{
Forward();
}
else if(l == HIGH && r == HIGH && c == HIGH) //Condition to stop/turn when all reading
{
if(Counter==1) //Condition to turn around 180 degrees
{
Turn180();
Counter=0;
}
else if(Counter==0) //Condition to stop
{
Stop();
}
}
else if(l == LOW && r == LOW && c == LOW) //Condition to stop when there is no reading
{
Stop();
}
else if((l == HIGH && r == LOW && c == LOW)||(l == HIGH && r == LOW && c == HIGH)) //Conditions to turn left
{
Left();
}
else if((l == LOW && r == HIGH && c == LOW)||(l == LOW && r == HIGH && c == HIGH)) //Conditions to turn right
{
Right();
}
}
