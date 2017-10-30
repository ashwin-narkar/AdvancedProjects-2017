#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>


#define CE 9
#define CS 10
#define green 20
char r[] = {'u'};
char *rPtr = r;
RF24 radiomodule(CE,CS);
bool received = false;
uint8_t i = 0;
uint8_t *p = &i;

void setup() {
  // put your setup code here, to run once:
  pinMode(CE, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SCK, INPUT);
  pinMode(green, OUTPUT);
  
  Serial.begin(9600);
  
  radiomodule.begin();
  radiomodule.setChannel(6);
  radiomodule.setPALevel(RF24_PA_MIN);
  radiomodule.setAddressWidth(5);
  uint8_t writeAddress[] = {0xe7,0xe7,0xe7,0xe7,0xe7};
  uint8_t readAddress[] = {0xC2,0xC2,0xC2,0xC2,0xC2};
  radiomodule.openReadingPipe(1,readAddress);
  //radiomodule.openWritingPipe(writeAddress);
  radiomodule.setCRCLength(RF24_CRC_16);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
//       delay(1000);
//   Serial.println("Reading");
// 
//    Serial.println((int) r[0]);
    radiomodule.startListening();
//  digitalWrite(green, HIGH);
//  delay(1000);
//  digitalWrite(green, LOW);
//  delay(1000);
    
    while (radiomodule.available(p)) {
      Serial.println("Available");
      radiomodule.read(rPtr, 2); 
    }
    radiomodule.printDetails();
    Serial.println();
    Serial.println();
    
}
     
     


