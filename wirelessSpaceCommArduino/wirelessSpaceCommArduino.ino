#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#define CSN 10
#define MOSI 11
#define MISO 12
#define SCK 13
#define CE 9


RF24 transmitter;
bool transmitting;
char c;


void setup() {
  // put your setup code here, to run once:
  transmitter(CE, CSN);
  pinMode(CSN, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(SCK, OUTPUT);
  pinMode(CE, OUTPUT);
  transmitter.begin();
  transmitter.setChannel(6);
  transmitter.setPALevel(RF24_PA_MIN);
  uint8_t writeAddress[] = {0xC2,0xC2,0xC2,0xC2,0xC2};
  uint8_t readAddress[] = {0xe7,0xe7,0xe7,0xe7,0xe7};
  transmitter.openWritingPipe(1,address);
  transmitter.openReadingPipe(2,readAddress);
  transmitting = true;
  c = 'a';
}

void loop() {
  // put your main code here, to run repeatedly:
  if (transmitting) {
    transmitter.write(&c,1);
  }
  transmitting = false;
  while (true);

}
