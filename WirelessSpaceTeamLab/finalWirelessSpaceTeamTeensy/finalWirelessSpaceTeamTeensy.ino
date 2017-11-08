#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>



#define CE 9
#define CS 10
#define green 18
#define blue 19
#define yellow 17

unsigned char r = 'a';
unsigned char x[] = {'Y','G','B'};
bool roundOver = false;
int i =0;

RF24 radiomodule(CE,CS);

String seq = "";
String playerInput = "";
int inputtedLen = 0;
int seqLength = 0;
int it = 1;



void setup() {
  // put your setup code here, to run once:
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(yellow,OUTPUT);
  Serial.begin(9600);
  
  radiomodule.begin();
  radiomodule.setChannel(6);
  radiomodule.setPALevel(RF24_PA_MIN);
  radiomodule.setDataRate(RF24_1MBPS);

  radiomodule.setAutoAck(1, true);
  radiomodule.setAutoAck(0, true);
  radiomodule.setPayloadSize(sizeof(unsigned char));
  radiomodule.openReadingPipe(1,0xe8e8e8e8e8);
  radiomodule.openWritingPipe(0x6161616161);
  radiomodule.setCRCLength(RF24_CRC_16);
  radiomodule.startListening();
  
  randomSeed(analogRead(5));
    delay(5000);
  
  generateSeq();
  Serial.println("About to Flash Sequence");
    flashSeq(); 
    Serial.print("Flashed Sequence: ");
    Serial.println(seq);
  //Serial.println(seq);
 
}

void loop() {
  // put your main code here, to run repeatedly:
 
//  Serial.print("Sequence: ");
//  Serial.println(seq);
//  Serial.print("Iteration ");
//  Serial.println(it);
//  it++;
  delay(1000);
  
    sendSeq(i); 
    unsigned char ack = listenForArduino();
    while (ack == '9') {
      ack = listenForArduino();
    }
    displayAck(ack);
  
  digitalWrite(green,HIGH);
  delay(400);
  digitalWrite(green,LOW);
  Serial.println("Correct!");
  i++;
  if (i == seqLength) {
    generateSeq();
    Serial.println("About to Flash Sequence");
    flashSeq(); 
    Serial.print("Flashed Sequence: ");
    Serial.println(seq);  
    i=0;
  }
}
     


