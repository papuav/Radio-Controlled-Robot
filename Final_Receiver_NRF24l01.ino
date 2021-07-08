
//Receiver Code
//Radio Controlled Arduino Robot
//Subscribe to YouTube Channel Papuav



//Add all the necessary library
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define enA 2  
#define in1 3
#define in2 4
#define enB 7   
#define in3 5
#define in4 6

RF24 radio(8,9); // CE, CSN
const byte address[6] = "00001";
char receivedData[32] = "";
int  xAxis, yAxis;
int motorSpeedA = 0;
int motorSpeedB = 0;
int joystick[2]; 


//Setup all the pins and the radio Module
void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

//Initial Condition of the motors  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void loop() {

  if (radio.available()) {   // If the NRF240L01 module received data
     
      radio.read( joystick, sizeof(joystick) );

    radio.read(&receivedData, sizeof(receivedData));
    yAxis = joystick[0];
    xAxis = joystick[1];
    
    Serial.println(yAxis);
    Serial.println(xAxis);

  }
  else if (radio.available()== 0 ){
    
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  Serial.println("Not Connected!");
  delay(30);  
    }
  
  if (yAxis < 470) {

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
  }
  else if (yAxis > 550) {

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);
  }
 else if (xAxis < 470) {

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    motorSpeedA = map(xAxis, 470, 0, 0, 255);
    motorSpeedB = map(xAxis, 470, 0, 0, 255);
  }
  else if (xAxis > 550) {

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    motorSpeedA = map(xAxis, 550, 1023, 0, 255);
    motorSpeedB = map(xAxis, 550, 1023, 0, 255);
  }

  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
}
