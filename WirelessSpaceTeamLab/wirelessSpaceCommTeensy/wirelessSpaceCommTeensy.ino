#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>


#define CE 9
#define CS 10
#define green 20
unsigned char r = 'a';

RF24 radiomodule(CE,CS);
bool received = false;

//byte addresses[][6] = {"1Node","2Node"};

void setup() {
  // put your setup code here, to run once:
 
  Serial.begin(9600);
  
  radiomodule.begin();
  radiomodule.setChannel(6);
  radiomodule.setPALevel(RF24_PA_MIN);
  radiomodule.setDataRate(RF24_1MBPS);
//  uint8_t writeAddress[] = {0xe7e7e7e7e7};
//  uint8_t readAddress[] = {0xC2C2C2C2C2};
  radiomodule.setAutoAck(1, true);
  radiomodule.setAutoAck(0, true);
  radiomodule.setPayloadSize(sizeof(unsigned char));
  radiomodule.openReadingPipe(1,0xe8e8e8e8e8);
  radiomodule.openWritingPipe(0x6161616161);
  radiomodule.setCRCLength(RF24_CRC_16);
  radiomodule.startListening();
  
}

void loop() {
  // put your main code here, to run repeatedly:

//       delay(1000);
//   Serial.println("Reading");
// 
//    Serial.println((int) r[0]);
    
//  digitalWrite(green, HIGH);
//  delay(1000);
//  digitalWrite(green, LOW);
    delay(100);
    Serial.print("Availability: ");
    Serial.println(radiomodule.available());
    if (radiomodule.available()) {
      
      radiomodule.read(&r, sizeof(unsigned char)); 
    }
    Serial.print("Received: ");
    Serial.println(r);
    //radiomodule.printDetails();
}
     
     


