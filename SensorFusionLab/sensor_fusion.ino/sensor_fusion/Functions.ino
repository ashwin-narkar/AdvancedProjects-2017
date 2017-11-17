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
