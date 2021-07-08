
//Transmitter Code
//Radio Controlled Arduino robot
//Subcribe to YouTube Channel Papuav


//Add all the necessary Library
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7,8); // CE, CSN
const byte address[6] = "00001";
char xyData[32] = "";
int joystick[2];

//Setup The radio module
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

//This is the main Loop 
void loop() {

  joystick[0] = analogRead(A0);
  joystick[1] = analogRead(A1);
  
  radio.write( joystick, sizeof(joystick) );
  Serial.println(joystick[0]);
  Serial.println(joystick[1]);
}
