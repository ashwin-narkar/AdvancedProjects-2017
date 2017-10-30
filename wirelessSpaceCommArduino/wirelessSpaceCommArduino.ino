
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

RF24 transmitter(CE, CSN);
bool transmitting;
char c[1];

void setup() {
  // put your setup code here, to run once:
  pinMode(CSN, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(SCK, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(blue, OUTPUT);
  
  Serial.begin(57600); 
  transmitter.begin();
  transmitter.setChannel(6);
  transmitter.setPALevel(RF24_PA_MIN);
  uint8_t writeAddress[] = {0xC2,0xC2,0xC2,0xC2,0xC2};
  uint8_t readAddress[] = {0xe7,0xe7,0xe7,0xe7,0xe7};
  transmitter.openWritingPipe(writeAddress);
  //transmitter.openReadingPipe(1,readAddress);
  transmitting = true;
  c[0] = 'a';
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(blue, HIGH);
  delay(1000);
  digitalWrite(blue, LOW);
  delay(1000);
  Serial.println("Working");
//  if (transmitting) {
//    transmitter.write(c,1);
//    Serial.println("sent");
//  }
  //Serial.println('a');
  //transmitting = false;
  //while (true);
}
