#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>


#define CE 9
#define CS 10
#define green 20

char r[] = {'u'};
RF24 radiomodule(CE,CS);
bool received = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(CE, INPUT);
  pinMode(CS, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SCK, INPUT);
  pinMode(green, OUTPUT);
  
  Serial.begin(9600);
  
  radiomodule.begin();
  radiomodule.setChannel(0b00000110);
  radiomodule.setPALevel(RF24_PA_MIN);
  uint8_t writeAddress[] = {0xe7,0xe7,0xe7,0xe7,0xe7};
  uint8_t readAddress[] = {0xC2,0xC2,0xC2,0xC2,0xC2};
  radiomodule.openReadingPipe(1,readAddress);
  radiomodule.openWritingPipe(writeAddress);
  radiomodule.setCRCLength(RF24_CRC_16);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  radiomodule.startListening();
  digitalWrite(green, HIGH);
  delay(1000);
  digitalWrite(green, LOW);
  delay(1000);
  if(radiomodule.available() && !received){
    Serial.println("Reading");
    radiomodule.read(r, sizeof(r));
    received = true;
  }
  else {
    Serial.println("Not available");
  }
  if (received == true) {
    radiomodule.stopListening();
  }
  Serial.println(r[0]);
}
