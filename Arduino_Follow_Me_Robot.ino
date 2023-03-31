//Arduino Human Following Robot
// Created By DIY Builder
// You have to install the AFMotor and NewPing library Before Uploading the sketch
// You can find all the required libraris from arduino library manager.
// Contact me on instagram for any query(Insta Id : diy.builder)
// Modified 7 Mar 2022
// Version 1.1


//librării:
#include<NewPing.h>           
#include<Servo.h>             
#include<AFMotor.h>           

#define RIGHT A2              // Senzorul IR drept conectat la portul A2 de la Arduino Uno:
#define LEFT A3               // Senzorul IR stâng conectat la portul A3 de la Arduino Uno:
#define TRIGGER_PIN A1        // Pinul Trigger conectat la portul A1 de la Arduino Uno:
#define ECHO_PIN A0           // Pinul Echo conectat la portul A0 de la Arduino Uno:
#define MAX_DISTANCE 200      // Distanța maximă:

unsigned int distance = 0;    // Variabilă ce stochează distanța înregistrată de senzorul ultrasonic:
unsigned int Right_Value = 0; //Variabilă ce stochează distanța înregistrată de la sunzorul IR drept:
unsigned int Left_Value = 0;  //Variabilă ce stochează distanța înregistrată de la sunzorul IR stâng:
  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  //NewPing setup of pins and maximum distance:

//se creează obiectele motor
AF_DCMotor Motor1(1,MOTOR12_1KHZ);
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);
AF_DCMotor Motor4(4,MOTOR34_1KHZ);

 Servo myservo; //se creează obiectul servo ce controlează servomotorul:
 int pos=0;     //variabilă ce stochează poziția servo:

void setup() { // funcția funcționează doar când plăcuța este conectată la o sursă de putere sau este resetată:
  
   Serial.begin(9600); //se inițializează comunicatrea serie la 9600 bits pe secundă:
   myservo.attach(10); //servomotorul atașat de portul 10 al plăcuței Arduino:
{
for(pos = 90; pos <= 180; pos += 1){    //merge de la 90° la 180°:
  myservo.write(pos);                   //servo se mișcă conform valorii variabilei pos:
  delay(15);                            //așteaptă 15 ms pentru ca servo să ajungă pe poziție:
  } 
for(pos = 180; pos >= 0; pos-= 1) {     // merge de la 180° la 0°:
  myservo.write(pos);                   //servo se mișcă conform valorii variabilei pos:
  delay(15);                            //așteaptă 15 ms pentru ca servo să ajungă pe poziție:
  }
for(pos = 0; pos<=90; pos += 1) {       //merge de la 0° la 90°:
  myservo.write(pos);                   //servo se mișcă conform valorii variabilei pos:
  delay(15);                            //așteaptă 15 ms pentru ca servo să ajungă pe poziție:
  }
}
   pinMode(RIGHT, INPUT); // analog pin RIGHT ca input:
   pinMode(LEFT, INPUT);  // analog pin LEFT ca input:
}


void loop() {                             
  
delay(50);                                        //așteaptă 50ms între pinguri:
distance = sonar.ping_cm();                       // trimite ping, ia distanța în cm și o stochează în variabila distance:
Serial.print("distance");                   


    Right_Value = digitalRead(RIGHT);             // citește valoarea de la IR drept:
    Left_Value = digitalRead(LEFT);               //citește la valoarea de la IR stâng:
 


if((distance > 1) && (distance < 15)){            //verficare dacă valoarea de la ultrasonic este între 1 și 15.
                                                  //dacă este adevărat se execută:
  //Merge în față:
  Motor1.setSpeed(130);  //definește motor1 viteză:
  Motor1.run(FORWARD);   //rotește motor1 în sensul acelor de ceas:
  Motor2.setSpeed(130);  //definește motor2 viteză:
  Motor2.run(FORWARD);   //rotește motor2 în sensul acelor de ceas:
  Motor3.setSpeed(130);  //definește motor3 viteză:
  Motor3.run(FORWARD);   //rotește motor3 în sensul acelor de ceas:
  Motor4.setSpeed(130);  //definește motor4 viteză:
  Motor4.run(FORWARD);   //rotește motor4 în sensul acelor de ceas:
  
}else if((Right_Value==0) && (Left_Value==1)) {   //dacă este adevărat se execută:
  
  //Virează stânga                                               
  Motor1.setSpeed(150);  //definește motor1 viteză:
  Motor1.run(FORWARD);   //rotește motor1 în sensul acelor de ceas:
  Motor2.setSpeed(150);  //definește motor2 viteză:
  Motor2.run(FORWARD);   //rotește motor2 în sensul acelor de ceas:
  Motor3.setSpeed(150);  //definește motor3 viteză:
  Motor3.run(BACKWARD);  //rotește motor3 în sens invers:
  Motor4.setSpeed(150);  //definește motor4 viteză:
  Motor4.run(BACKWARD);  //rotește motor3 în sens invers:
  delay(150);
  
}else if((Right_Value==1)&&(Left_Value==0)) {     //dacă este adevărat se execută:

  //Virează dreapta
  Motor1.setSpeed(150);  //definește motor1 viteză:
  Motor1.run(BACKWARD);  //rotește motor1 în sens invers:
  Motor2.setSpeed(150);  //definește motor2 viteză:
  Motor2.run(BACKWARD);  //rotește motor2 în sens invers:
  Motor3.setSpeed(150);  //definește motor3 viteză:
  Motor3.run(FORWARD);   //rotește motor3 în sensul acelor de ceas:
  Motor4.setSpeed(150);  //definește motor4 viteză:
  Motor4.run(FORWARD);   //rotește motor4 în sensul acelor de ceas:
  delay(150);
  
}else if(distance > 15) {                         //dacă este adevărat se execută:
  
  //Stop
  Motor1.setSpeed(0);    //definește motor1 viteză:
  Motor1.run(RELEASE);   //stop motor1:
  Motor2.setSpeed(0);    //definește motor2 viteză:
  Motor2.run(RELEASE);   //stop motor2:
  Motor3.setSpeed(0);    //definește motor3 viteză:
  Motor3.run(RELEASE);   //stop motor3:
  Motor4.setSpeed(0);    //definește motor4 viteză:
  Motor4.run(RELEASE);   //stop motor4:
}
}
