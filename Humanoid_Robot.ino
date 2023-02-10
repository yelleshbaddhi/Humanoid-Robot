#include <NewPing.h>
#include<Servo.h>
Servo myservo;

#define Trig 11
#define Echo 12

#define F_motor_speed 75
#define F_motor_speed_adj 50

#define min_distance 10
#define max_distance 30

#define IR_SENSOR_RIGHT 2
#define IR_SENSOR_LEFT 4

//Right motor
int enableRightMotor=5;
int rightMotorPin1=7;
int rightMotorPin2=8;

//Left motor
int enableLeftMotor=6;
int leftMotorPin1=9;
int leftMotorPin2=10;

NewPing mySensor(Trig, Echo, 400);
int pos=0;
void setup()
{
  // put your setup code here, to run once:
  myservo.attach(3);
  for(pos=0;pos<180;pos++){
    myservo.write(pos);
    delay(15);
  }
  for(pos=180;pos>=90;pos--){
    myservo.write(pos);
    delay(15);
  }
  delay(1000);
  
  
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0,0);   
}


void loop()
{
  int distance = mySensor.ping_cm();
  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

  
  if (rightIRSensorValue == 0 && leftIRSensorValue == 1 )
  {
      rotateMotor(F_motor_speed - F_motor_speed_adj, F_motor_speed + F_motor_speed_adj ); 
  }
  else if (rightIRSensorValue == 1 && leftIRSensorValue == 0 )
  {
      rotateMotor(F_motor_speed + F_motor_speed_adj, F_motor_speed - F_motor_speed_adj); 
  }
  else if (distance >= min_distance && distance <= max_distance)
  {
    rotateMotor(F_motor_speed, F_motor_speed);
  }
  else 
  {
    rotateMotor(0, 0);
  }
}


void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else 
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}
