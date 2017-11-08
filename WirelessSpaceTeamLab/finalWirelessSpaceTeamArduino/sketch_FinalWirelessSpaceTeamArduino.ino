#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#define CSN 10
#define CE 9
#define readingPipe 1
#define writingPipe 0

#define yellowButton 4
#define blueButton 5
#define greenButton 6

RF24 radio(CE, CSN);
unsigned char buttonPushed = 'z';
bool risingEdgeYellow = false;
bool risingEdgeBlue = false;
bool risingEdgeGreen = false;
bool previousReadingYellow = true;
bool previousReadingBlue = true;
bool previousReadingGreen = true;

bool roundOver = false;
int i = 0;

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
  radio.setAutoAck(readingPipe, true);
  radio.setAutoAck(writingPipe, true);
  radio.startListening();

  radio.openReadingPipe(1, 0x6161616161);
  radio.openWritingPipe(0xe8e8e8e8e8);

  pinMode(greenButton,INPUT);
  pinMode(blueButton,INPUT);
  pinMode(yellowButton,INPUT);
  
}

unsigned char c = 'z';

void loop() {
  // put your main code here, to run repeatedly:
  roundOver = false;
  
    radio.startListening();
    Serial.println("Not Picked Up");
    while(!radio.available());
    Serial.println("Listening for Package");
    radio.read(&c,sizeof(c));
   
  while (!roundOver) { 
    buttonPushed = 'z';
    Serial.println("Listening for Button");
    
    listenForPress();

    if(buttonPushed != 'z'){
      
      if(checkSeq(buttonPushed,c)){
       radio.stopListening();
       unsigned char i = '1';
       while(!radio.write(&i,sizeof(unsigned char)));
       radio.startListening();
       Serial.println("Right");
      }
      else{
       radio.stopListening();
       unsigned char i = '0';
       radio.write(&i,sizeof(unsigned char));
       radio.startListening();
       Serial.println("Wrong");
      }
      roundOver = true;
    }
  }
  delay(200);
}
