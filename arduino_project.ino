#include "AFMotor.h"
#include <Servo.h>
#define echopin A0 // echo pin
#define trigpin A5 // Trigger pin
Servo myservo;
const int MOTOR_1 = 1; 
const int MOTOR_2 = 2; 
const int MOTOR_3 = 3; 
const int MOTOR_4 = 4; 
AF_DCMotor motor1(MOTOR_1, MOTOR12_64KHZ); // create motor object
AF_DCMotor motor2(MOTOR_2, MOTOR12_64KHZ); // create motor object
AF_DCMotor motor3(MOTOR_3, MOTOR12_64KHZ); // create motor object
AF_DCMotor motor4(MOTOR_4, MOTOR12_64KHZ); // create motor object
int d_L, d_F, d_R;
long duration;
int set = 20;
void setup() 
{
  Serial.begin(9600);           // Initialize serial port
  Serial.println("Start");
  myservo.attach(10);
  myservo.write(90);
  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  motor1.setSpeed(255);          // set the motor speed to 0-255
  motor2.setSpeed(255);
  motor3.setSpeed(255);          // set the motor speed to 0-255
  motor4.setSpeed(255);
}

void loop() {
 d_F = data();
 Serial.print("S=");
 Serial.println(d_F);
  if (d_F > set)
  {
    Serial.println("Forward");
    motor1.run(FORWARD);         // turn it on going forward
    motor2.run(FORWARD); 
    motor3.run(FORWARD);         // turn it on going forward
    motor4.run(FORWARD); 
  }
  else
  {
    checkdir();
  }
}
long data()               //This function checks the distance using ultrasonic sensor and returns it
{
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(echopin, HIGH);      //pulseIn() Returns the duration in which the echo of the pulse is recieved.
  return duration*0.034/2;                //Multiplying the duration by the speed of light and dividing by 2 to get one way distance of the pulse(echo) wave
}
void compDis()
{
  if (d_L > d_R)          //If left distance greater than right distance...turning towards left
  {
    Serial.println("Turning Left");
    motor1.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD); 
    motor2.run(FORWARD);
    delay(800);
  }
  else if (d_R > d_L)     //If RIGHT distance greater than LEFT distance...turning towards Right
  {
    Serial.println("Turning Right");
    motor1.run(FORWARD); 
    motor2.run(BACKWARD);
    motor3.run(FORWARD); 
    motor4.run(BACKWARD); 
    delay(800);
  }
}
void checkdir()
{
    Serial.println("Stop");
    motor1.run(RELEASE);         // stopped
    motor2.run(RELEASE);
    motor3.run(RELEASE);         // stopped
    motor4.run(RELEASE);
    myservo.write(0);           //Turning the servo motor towards Right
    delay(300);
    d_R = data();        //Reading the distance(right)
    delay(100);
    myservo.write(180);         //Turning the servo motor towards Left
    delay(500);
    d_L = data();        //Reading the Distance(left)
    delay(100);
    myservo.write(90);          //Turning towards front
    delay(300);
    compDis();          //Comparing Distances of both directions using function
}

