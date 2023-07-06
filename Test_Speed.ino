#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth_nash(4, 2);

Servo rule;
int gradus = 11;
int speed1 = 125;
int speed2 = 125;
char INBL;
boolean la = 1;
boolean trig = 0;
char Aktiv = '0';
bool start = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT);
  pinMode(2, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  bluetooth_nash.begin(9600);
  pinMode(10, OUTPUT);
  rule.attach(10, 650, 1100);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  analogWrite(5, 0);
  analogWrite(6, 0);  
  while(!start){
    if(bluetooth_nash.available() ){
      if(bluetooth_nash.read() == 'X') start = true;
    }
  }
  analogWrite(5, 125);
  analogWrite(6, 125);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeated  
  if(bluetooth_nash.available() & start == true){
    INBL = bluetooth_nash.read();
    switch (INBL){
      case 'R':
        while(bluetooth_nash.read() != 'S'){
            if(gradus < 170){
              ++gradus;
              rule.write(gradus);              
            }
        }      
        break;
      case 'L':
        while(bluetooth_nash.read() != 'S'){
          if(gradus > 10){
            ++gradus;
            rule.write(gradus);
          }
        }           
        break;
      case 'F':
        while(bluetooth_nash.read() != 'S'){
          if(speed1 < 254){
            ++speed1;
            analogWrite(5, speed1);
            analogWrite(6, speed1);            
          }          
        }
        break;
      case 'B':
        while(bluetooth_nash.read() != 'S'){
          if(speed1 > -256){
            --speed1;
            analogWrite(5, speed1);
            analogWrite(6, speed1);            
          }
        }
        break;
      case 'H':
        while(bluetooth_nash.read() != 'S'){
          if(speed1 > -256){
            --speed1;
            analogWrite(5, speed2);
            analogWrite(6, speed2);            
          }
        }
        break;
      case 'I':
        while(bluetooth_nash.read() != 'S'){
          if(speed1 < 254){
            ++speed2;
            analogWrite(5, speed2);
            analogWrite(6, speed2);            
          }          
        }
        break;
      case 'x':
        start = false; 
        break;
    }
    Serial.println(INBL);
  }
  if(speed1 > 0){
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    analogWrite(5, speed1);    
  }else{
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
    analogWrite(5, -speed1);
  }
  if(speed2 > 0){
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    analogWrite(6, speed2);
  }else{
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    analogWrite(6, -speed2);  
  }
  delay(100);
  if(bluetooth_nash.available() & INBL == 'X') start = true;
}
//49285
