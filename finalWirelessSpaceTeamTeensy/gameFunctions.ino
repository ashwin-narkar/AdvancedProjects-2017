unsigned char listenForArduino(){
  radiomodule.startListening();
  unsigned char c = '9';
  while(!radiomodule.available());
  if (radiomodule.available()){
    radiomodule.read(&c,sizeof(unsigned char));    
  }
  return c;
}

void sendSeq(int index){
  radiomodule.stopListening();
  unsigned char x = seq[index];
  while (!radiomodule.write(&x,sizeof(unsigned char))){
    Serial.println("Package Not sent yet ");
    delay(400);
  }
  Serial.println("Package Sent ");
}

void displayAck(unsigned char corr){
  if (corr == '0') {
    digitalWrite(blue,HIGH);
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


