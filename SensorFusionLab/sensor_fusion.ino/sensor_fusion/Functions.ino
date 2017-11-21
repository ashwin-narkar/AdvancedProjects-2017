void setupRegisters() {
  Wire.begin();

  uint8_t data = 0;
  uint8_t *buffr = &data;
  Serial.begin(115200);
  

  Serial.print("PWR_MGMT_1 before: ");
  readReg(PWR_MGMT_1, &data, 1);
  Serial.println(data,BIN);
  // PWR_MGMT_1 set bits [6] to 0
  readReg(PWR_MGMT_1, &data, 1);
  data &= 0b10111111;
  writeReg(PWR_MGMT_1, &data, 1);
  readReg(PWR_MGMT_1, &data, 1);
  Serial.println(data,BIN);

  // GYRO_CONFIG set bits[4:3] to 11b
  Serial.print("GYRO_CONFIG before: ");
  readReg(GYRO_CONFIG, &data, 1);
  Serial.println(data,BIN);
  
  readReg(GYRO_CONFIG, &data, 1);
  
  //data |= 0b00011000;
  data = 0b00011000;
 
  
  writeReg(GYRO_CONFIG, &data, 1);
  readReg(GYRO_CONFIG, &data, 1);
  Serial.println(data, BIN);

  // CONFIG set bits [2:0] to 000b
  Serial.print("CONFIG before: ");
  readReg(CONFIG, &data, 1);
  Serial.println(data, BIN);
  
  readReg(CONFIG, &data, 1);
 
  data &= 0b11111000;
  
  writeReg(CONFIG, &data, 1);
  readReg(CONFIG, &data, 1);
  Serial.println(data, BIN);
}

void biasCorrect() {
  xAccelBias = 0;
  yAccelBias = 0;
  zAccelBias = 0;
  xGyroBias = 0;
  yGyroBias = 0;
  zGyroBias = 0;
  if (getStatusReg()){
    for (int i=0;i<5;i++) {
      for (int i=0;i<10;i++) {
        xAccelBias += getAccelX();
      }
      xAccelBias /=10;
    }  
    for (int i=0;i<5;i++) {
      for (int i=0;i<10;i++) {
        yAccelBias += getAccelY();
      }
      yAccelBias /=10;
    }  
    for (int i=0;i<5;i++) {
      for (int i=0;i<10;i++) {
        zAccelBias += getAccelZ();
      }
      zAccelBias /=10;
    }
    
    for (int i=0;i<5;i++) {
      for (int i=0;i<10;i++) {
        xGyroBias += getGyroX();
      }
      xGyroBias /=10;
    }
    for (int i=0;i<5;i++) {
      for (int i=0;i<10;i++) {
        yGyroBias += getGyroY();
      }
      yGyroBias /=10;
    }
    for (int i=0;i<5;i++) {
      for (int i=0;i<10;i++) {
        zGyroBias += getGyroZ();
      }
      zGyroBias /=10;
    }
    
  }
}

int getStatusReg() {
  uint8_t data = 0;
  readReg(INT_STATUS,&data,1);
  data &= 1;
  return data;
}

int getAccelX(){
   int xAccel = 0;
   uint8_t data = 0;
   readReg(ACCEL_XOUT_H,&data,1);
   xAccel = data << 8;
   data = 0;
   readReg(ACCEL_XOUT_L,&data,1);
   xAccel += data;
   return xAccel;
}

int getAccelY(){
   int yAccel = 0;
   uint8_t data = 0;
   readReg(ACCEL_YOUT_H,&data,1);
   yAccel = data << 8;
   data = 0;
   readReg(ACCEL_YOUT_L,&data,1);
   yAccel += data;
   return yAccel;
}

int getAccelZ(){
   int zAccel = 0;
   uint8_t data = 0;
   readReg(ACCEL_ZOUT_H,&data,1);
   zAccel = data << 8;
   data = 0;
   readReg(ACCEL_ZOUT_L,&data,1);
   zAccel += data;
   return zAccel;
}

int getGyroX(){
   int xGyro = 0;
   uint8_t data = 0;
   readReg(GYRO_XOUT_H,&data,1);
   
   xGyro = data << 8;
   data = 0;
   readReg(GYRO_XOUT_L,&data,1);
   xGyro += data;
   return xGyro;
}

int getGyroY(){
   int yGyro = 0;
   uint8_t data = 0;
   readReg(GYRO_YOUT_H,&data,1);
   yGyro = data << 8;
   data = 0;
   readReg(GYRO_YOUT_L,&data,1);
   yGyro += data;
   return yGyro;
}

int getGyroZ(){
   int zGyro = 0;
   uint8_t data = 0;
   readReg(GYRO_ZOUT_H,&data,1);
   zGyro = data << 8;
   data = 0;
   readReg(GYRO_ZOUT_L,&data,1);
   zGyro += data;
   return zGyro;
}

void quaternionator(struct vector* v){
  magnitude = vector_normalize(&gyro, &gyro);      //finding angular velocity of gyroscope vector
  currentAngle = -(magnitude / 16.4) * (3.14/180);  //finding velocity from angular velocity
  deltaTime = millis() - deltaTime;
  currentAngle *= (deltaTime/1000.0);
 
  /*if(!first_time_run){
    pastAngle = currentAngle;
    first_time_run = true;
  }
  else{
    deltaAngle = (currentAngle - pastAngle) * deltaTime * 1000;
    pastAngle = currentAngle + deltaAngle;
  }*/
  struct quaternion updateQuater;
  quaternion_create(&gyro, currentAngle, &updateQuater);
  
//  Serial.print("DeltaTime: ");
//  Serial.println(deltaTime);

  quaternion_rotate(v, &updateQuater, v);
}

void filterAndCombine() {
  
  filteredVect.x = (accel.x*accelWeight) + (filteredVect.x*(1-accelWeight));
  filteredVect.y = (accel.y*accelWeight) + (filteredVect.y*(1-accelWeight));
  filteredVect.z = (accel.z*accelWeight) + (filteredVect.z*(1-accelWeight));
  
}




void angleCalculations(){
  //gyro
  angle_x += gyro.x * 0.0000611;
  angle_y += gyro.y * 0.0000611;
  angle_x += angle_y * sin(gyro.z * 0.000001066);
  angle_y += angle_x * sin(gyro.z * 0.000001066);

  //accelerometer
  total_accel_vector = sqrt((accel.x*accel.x) + (accel.y*accel.y) + (accel.z*accel.z));
  angle_x_acc = asin((float)accel.y/total_accel_vector) * 57.296;
  angle_y_acc = asin((float)accel.x/total_accel_vector) * -57.296;

  //Serial.println(total_accel_vector);

  //pitch and roll accelerometer calibrations
  angle_x_acc -= 0.0;
  angle_y_acc -= 0.0;

 if(first_time_run){
    angle_x = angle_x * 0.9996 + angle_x_acc * 0.0004;    
    angle_y = angle_y * 0.9996 + angle_y_acc * 0.0004; 
 }
 else{
  angle_x = angle_x_acc;
  angle_y = angle_y_acc;
  first_time_run = true;
 }

 //To dampen the pitch and roll angles a complementary filter is used
 angle_x_output = angle_x_output * 0.9 + angle_x * 0.1;
 angle_y_output = angle_y_output * 0.9 + angle_y * 0.1;

 while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
 loop_timer = micros(); //Reset the loop timer
}
