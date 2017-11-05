void risingEdgeDetect(){

//  if(digitalRead(yellowButton) != 0){
//    risingEdgeYellow = true;
//    Serial.println("Here1");
//  }
//  if(digitalRead(blueButton) != 0){
//    risingEdgeBlue = true;
//    Serial.println("Here2");
//  }
//  if(digitalRead(greenButton) != 0){
//    risingEdgeGreen = true;
//    Serial.println("Here3");
//  }
//  if(digitalRead(yellowButton) == 0){
//    risingEdgeYellow = false;
//  }
//  if(digitalRead(blueButton) == 0){
//    risingEdgeBlue = false;
//  }
//  if(digitalRead(greenButton) == 0){
//    risingEdgeGreen = false;
//  }
  
  if(digitalRead(yellowButton) != 0){
    previousReadingYellow = risingEdgeYellow;
    risingEdgeYellow = true;
    //Serial.println("Here1");
  }
  if(digitalRead(blueButton) != 0){
    previousReadingBlue = risingEdgeBlue;
    risingEdgeBlue = true;
    //Serial.println("Here2");
  }
  if(digitalRead(greenButton) != 0){
    previousReadingGreen = risingEdgeGreen;
    risingEdgeGreen = true;
    //Serial.println("Here3");
  }
  if(digitalRead(yellowButton) == 0){
    previousReadingYellow = risingEdgeYellow;
    risingEdgeYellow = false;
  }
  if(digitalRead(blueButton) == 0){
    previousReadingBlue = risingEdgeBlue;
    risingEdgeBlue = false;
  }
  if(digitalRead(greenButton) == 0){
    previousReadingGreen = risingEdgeGreen;
    risingEdgeGreen = false;
  }
}

void listenForPress(){
  risingEdgeDetect();

//  if(risingEdgeYellow){
//    buttonPushed = 'Y';
//    Serial.println("Yellow Pressed");
//  }
//  if(risingEdgeBlue){
//    buttonPushed = 'B';
//    Serial.println("Blue Pressed");
//  }
//  if(risingEdgeGreen){
//    buttonPushed = 'G';
//    Serial.println("Green Pressed");
//  }
  
  if(risingEdgeYellow && !previousReadingYellow){
    buttonPushed = 'Y';
    //Serial.println("Yellow Pressed");
  }
  if(risingEdgeBlue && !previousReadingBlue){
    buttonPushed = 'B';
    //Serial.println("Blue Pressed");
  }
  if(risingEdgeGreen && !previousReadingGreen){
    buttonPushed = 'G';
    //Serial.println("Green Pressed");
  }
}

/*void addPress(){
//  radio.stopListening();
//  Serial.println(radio.write(&buttonPushed,sizeof(buttonPushed)));
//  buttonPushed = 'z';
//  radio.startListening();
  Player.combo += buttonPushed;
  buttonPushed = 'z';
  i++;
}*/

bool checkSeq(unsigned char player, unsigned char correct) {
  if (player == correct){
    return true;
  }
  else {
    return false;
  }
}


