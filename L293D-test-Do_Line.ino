#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

/************************************************/
AF_DCMotor motor1(2);        
AF_DCMotor motor2(3);        

Servo myservo;              

/***********************IRcode Definition  *************************/
#include "UCNEC.h"
int32_t temp = 0;
UCNEC myIR(10);             

#define F 16718055
#define B 16732845
#define L 16713975
#define R 16734885
#define S 16719075
#define track       16717545          
#define ultra       16718310           
#define ble         16715250          


#define ECHO_PIN A0         
#define TRIG_PIN A1          

#define MAX_DISTANCE 200 
#define MAX_SPEED 235       
#define MAX_SPEED_OFFSET 20  

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
boolean goesForward=false;
int distance = 100;
int speedSet = 0;
char command; 

int lechA = 0;         
int lechB = 0;           
int dugme=1;
/*************************Define Line Track pins************************************/
const int SensorLeft   = A5;     
const int SensorMiddle = A4;       
const int SensorRight  = A3;       
int SL;    //Status of Left line track sensor
int SM;    //Status of Midd line track sensor
int SR;    //Status of Righ line track sensor

unsigned char Dift=1;

void setup() {  
   
//    
 myIR.begin();

     
//    
    pinMode(SensorLeft,  INPUT);    //Init left sensor
    pinMode(SensorMiddle, INPUT);   //Init Middle sensor
    pinMode(SensorRight, INPUT);    //Init Right sensor
 

}
void loop(){
      if(myIR.available())
      {
            temp =  myIR.read();
      }
             
      if (temp == F)      {go(160,160);} 
      else if (temp == B) {back(160,160);} 
      else if (temp == L) {left(200,200);} 
      else if (temp == R) {right(200,200);} 
      else if (temp == S) {Stop();temp=0;}
      else if (temp == track) 
      {
              Dift=0;
              while(temp == track)
              {
//                      int distance = sonar.ping_cm();
//
//                if (distance == 0) {
//                        distance = 30;
//                }
//                
//                if(distance <=20) {
//                            Stop();
//                            delay(100);
//                        right(150,150);
//                        delay(150);
//                            Stop();
//                            delay(100);
//                        go(200,200);
//                        delay(800);
//                            Stop();
//                            delay(300);
//                        left(200,200);
//                        delay(210);
//                            Stop();
//                            delay(300);
//                        go(180,200);
//                        delay(700);
//                            Stop();
//                            delay(100);
//                        do{
//                            left(40,160);
//                            SL = digitalRead(SensorLeft);
//                            SM = digitalRead(SensorMiddle);
//                            SR = digitalRead(SensorRight);
//                        }while((SL==LOW)&&(SM==LOW)&&(SR==LOW));
//                            
//                            Stop();
//                            delay(100);
//                        do{
//                            right(160,40);
//                            SL = digitalRead(SensorLeft);
//                            SM = digitalRead(SensorMiddle);
//                            SR = digitalRead(SensorRight);
//                        }while((SL==LOW)&&(SM==LOW)&&(SR==LOW));
//                        
//                            //delay(500);
//                            //go(160);
//                            //delay(700);
//                            //right(250,250);
//                            //delay(500);
//                }
          
                /****************************************/
//                temp =  myIR.read();
                
                SL = digitalRead(SensorLeft);
                SM = digitalRead(SensorMiddle);
                SR = digitalRead(SensorRight);
                
                //right fast 20 200
                if (SM == HIGH && SR == HIGH && SL == LOW)
                {
                      go(80,150);delay(1000);
                }
                if (SM == HIGH && SR == LOW && SL == HIGH)
                {
                      go(150,80);delay(1000);
              
                }
                if (SM == HIGH && SR == LOW && SL == LOW)
                {
                      go(100,100);delay(1000);
                }
                if(SM == LOW && SR == LOW && SL == HIGH)
                {
                      go(70,150);delay(1000);
                }
                if(SM == LOW && SR == HIGH && SL == LOW)
                {
                      go(150,70);delay(1000);
                }
                if(SM == LOW && SR == LOW && SL == LOW)
                {
                      go(100,100);delay(1000);
                }
                else
                {
                      Stop(); delay(1000);
                }
// if (SM == HIGH && SR == HIGH && SL == LOW)
//      {
//            goRight(160,40);delay(100);
//      }
//      if (SM == HIGH && SR == LOW && SL == HIGH)
//      {
//            goLeft(40,160);delay(100);
//    
//      }
//      if (SM == HIGH && SR == LOW && SL == LOW)
//      {
//            forward();
//      }
//      if(SM == LOW && SR == LOW && SL == HIGH)
//      {
//            goLeft(200,80);delay(100);
//      }
//      if(SM == LOW && SR == HIGH && SL == LOW)
//      {
//            goRight(80,200);delay(100);
//      }
//      else
//      {
//            Stop(); delay(100);
//      }
             }
        }
        else if( temp == ultra){ // Tranh vat can
            myservo.attach(9);         //tương ứng SERVO2; NẾU CẮM SERVO1 - KHAI  myservo.attach(10);
            myservo.write(95);         //Chỉnh lại góc quay SG90: 85,95,105,... sao cho cảm biến siêu âm thẳng với xe
            delay(1000);
            distance = readPing();
            delay(100);
            distance = readPing();
            delay(100);
            distance = readPing();
            delay(100);
            distance = readPing();
            delay(100);
           long duration,distance;
           Serial.begin(9600);
           while(dugme==1)
           { 
              
               int distanceR = 0;
               int distanceL =  0;
               delay(40);
               if(distance<=24)
               {
                    moveStop();
                    delay(100);
                    moveBackward();
                    delay(300);
                    moveStop();
                    delay(200);
                    distanceR = lookRight();
                    delay(200);
                    distanceL = lookLeft();
                    delay(200);
                    if(distanceR>=distanceL)
                    {
                      turnRight();
                      moveStop();
                    }else
                    {
                      turnLeft();
                      moveStop();
                    }
               }else
               {
                forward();
               }
               distance = readPing();
           }
        }
        else 
        {
            Stop();
            temp=0;
        }
      
}
void go(int a, int b)
{
  motor1.setSpeed(b+lechB); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(a+lechA); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
}
void back(int a, int b)
{
  motor1.setSpeed(b+lechB); 
  motor1.run(BACKWARD); 
  motor2.setSpeed(a+lechA); 
  motor2.run(BACKWARD); 
}
void left(int a, int b)
{
  motor1.setSpeed(b+lechB); 
  motor1.run(FORWARD); 
  motor2.setSpeed(a+lechA);
  motor2.run(BACKWARD); 
}
void right(int a, int b)
{
  motor1.setSpeed(b+lechB);
  motor1.run(BACKWARD); 
  motor2.setSpeed(a+lechA);  
  motor2.run(FORWARD); 
}

void Stop()
{
  motor1.setSpeed(0);
  motor2.run(RELEASE); 
  motor2.setSpeed(0);
  motor2.run(RELEASE); 
}
void stopAvoiding()
{
  //dugme=0;
  motor1.setSpeed(0);
  motor2.run(RELEASE); 
  motor2.setSpeed(0);
  motor2.run(RELEASE); 
}

int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(105); 
    return distance;
}
int lookLeft()
{
    myservo.write(160); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(105); 
    return distance;
    delay(100);
}
int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  } 
void moveForward() {
 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);   
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
   }
  }
}
void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
  }
}  
void turnRight() {
  motor2.run(FORWARD);
  motor1.run(BACKWARD);     
  delay(300);
  motor2.run(FORWARD);      
  motor1.run(FORWARD);      
} 
void turnLeft() {
  motor2.run(BACKWARD);     
  motor1.run(FORWARD);     
  delay(300);
  motor2.run(FORWARD);     
  motor1.run(FORWARD);
}    
void forward()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
}
void aheadLeft()
{
  motor1.setSpeed(255); 
  motor1.run(FORWARD); 
  motor2.setSpeed(125); 
  motor2.run(FORWARD); 
}
void aheadRight()
{
  motor1.setSpeed(125); 
  motor1.run(FORWARD); 
  motor2.setSpeed(255); 
  motor2.run(FORWARD); 
}
void goLeft(int a, int b)
{
  motor1.setSpeed(b); 
  motor1.run(FORWARD); 
  motor2.setSpeed(a); 
  motor2.run(FORWARD); 
}
void goRight(int a, int b)
{
  motor1.setSpeed(b); 
  motor1.run(FORWARD); 
  motor2.setSpeed(a); 
  motor2.run(FORWARD); 
}
