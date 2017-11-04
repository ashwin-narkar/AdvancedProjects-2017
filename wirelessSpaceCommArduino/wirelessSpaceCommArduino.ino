#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#define CSN 10
#define MOSI 11
#define MISO 12
#define SCK 13
#define CE 9
#define blue 3

RF24 radio(CE, CSN);
unsigned char c;

void setup() {
  // put your setup code here, to run once:

  printf_begin();
  Serial.begin(9600); 
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setPayloadSize(sizeof(unsigned char));
  radio.setChannel(6);
  radio.setCRCLength(RF24_CRC_16);
  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(1, true);
  radio.setAutoAck(0, true);
  radio.startListening();

  radio.openReadingPipe(1, 0x6161616161);
  radio.openWritingPipe(0xe8e8e8e8e8);
 
  c = 'z';
  
  
}

void loop() {
  // put your main code here, to run repeatedly:

  radio.stopListening();
  
  radio.write(&c,sizeof(unsigned char));
  //Serial.println("sent");
  c++;
  c = c%128;
  //Serial.println('a');
  Serial.println(c);
  delay(100);
  
}
