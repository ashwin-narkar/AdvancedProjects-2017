#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>


#define CE 15
#define CS 10

char receivedLetter = 'u';
RF24 radiomodule(CE,CS);

void setup() {
  // put your setup code here, to run once:
  radiomodule.begin();
  radiomodule.setChannel(0b00000110);
  radiomodule.setPALevel(RF24_PA_MIN);
  radiomodule.openReadingPipe(1,0xc2c2c2c2c2);
  radiomodule.openWritingPipe(0xe7e7e7e7e7);
  radiomodule.setCRCLength(RF24_CRC_16);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  radiomodule.startListening();
  if(radiomodule.available()){
    radiomodule.read(&receivedLetter, sizeof(receivedLetter));
  }
  radiomodule.stopListening();
  Serial.println(receivedLetter);
}
