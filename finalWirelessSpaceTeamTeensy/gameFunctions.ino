unsigned char listenForArduino(){
  radiomodule.startListening();
  unsigned char c = '9';
  while(!radiomodule.available());
  if (radiomodule.available()){
    radiomodule.read(&c,sizeof(unsigned char));  
    Serial.print("Acknowledgement: ");
    Serial.println((char)c);  
  }
  return c;
}

void sendSeq(int index){
  radiomodule.stopListening();
  unsigned char x = seq[index];
  while (!radiomodule.write(&x,sizeof(unsigned char))){
    Serial.print("Package Not sent yet: ");
    Serial.println((char)x);
    delay(100);
  }
  Serial.println("Package Sent ");
}

void displayAck(unsigned char corr){
  if (corr == '0') {
    digitalWrite(blue,HIGH);
    Serial.println("GAME OVER");
    while(true);
  }
}


void generateSeq() {
  int i = random(0,3);
  //Serial.print("Random Number ");
  //Serial.println(i);
  unsigned char newC = x[i];
  //Serial.print("Random Char ");
  //Serial.println((char)newC);
  seq.concat((char)newC);
  seqLength++;
 
}



void flashSeq() {
  int i = 0;
  int color = 0;
  while(i<seqLength) {
    switch(seq[i]) {
      case 'G':
        color = green;
        break;
      case 'Y':
        color = yellow;
        break;
      case 'B':
        color = blue;
        break;
    }
    i++;
    digitalWrite(color,HIGH);
    delay(400);
    digitalWrite(color,LOW);
    delay(400);
  }
}


