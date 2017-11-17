#include <sensor_fusion.h>
#include <printf.h>
#include <Wire.h>


// PWR_MGMT_1 to take IMU out of sleep mode
// pg. 40 of datasheet: Register 0x6B set sleep mode bit to 0 (bit 6)

// GYRO_CONFIG to largest possible full-scale range to enable
// pg. 14 of datasheet: Register 0x1B set FS_SEL Bits[4:3] to 3 (11b) for largest
// full-scale range of 2000 deg/s

// detection of high-velocity rotations
// CONFIG register to largest possible bandwidth
// pg. 13 of datasheet: Register 0x1A set DLPF_CFG Bits[2:0] to 0 (000b)

const int PWR_MGMT_1 = 0x6B;
const int GYRO_CONFIG = 0x1B;
const int CONFIG = 0x1A;

const int MPU_addr = 0x68;  // I2C address of the MPU-6050

void setup() {

  Wire.begin();

  
  Serial.begin(9600);
  
  uint8_t data = 9; 
  uint8_t* buffr = &data;

//  for (int i=0;i<10;i++) {
//    data = i;
//    Serial.print("Iteration: ");
//    Serial.println(data);
    writeReg(PWR_MGMT_1, &data, 1);
    readReg(PWR_MGMT_1, &data, 1);
    Serial.println("Read register done");
    Serial.print("PWR_MGMT_1 before: ");
    Serial.println(data);
    Serial.println();
    delay(100);
  //}
  // PWR_MGMT_1 set bits [6] to 0
  //readReg(PWR_MGMT_1, &data, 1);

  //data = 9; 
  //writeReg(PWR_MGMT_1, &data, 1);
  //delay(4000);
  //readReg(PWR_MGMT_1, &data, 1);
  //data = *data;
  //Serial.println(data);

//  // GYRO_CONFIG set bits[4:3] to 11b
//  Serial.print("GYRO_CONFIG before: ");
//  readReg(GYRO_CONFIG, &data, 1);
//  Serial.println(data);
//  
//  readReg(GYRO_CONFIG, &data, 1);
////  data = *buffr;
////  data |= 00011000;
////  buffr = &data;
//  
//  writeReg(GYRO_CONFIG, &data, 1);
//  readReg(GYRO_CONFIG, &data, 1);
//  Serial.println(data, BIN);
//
//  // CONFIG set bits [2:0] to 000b
//  Serial.print("CONFIG before: ");
//  readReg(CONFIG, buffr, 1);
//  Serial.println(*buffr, BIN);
//  
//  readReg(CONFIG, buffr, 1);
//  data = *buffr;
//  data &= 11111000;
//  buffr = &data;
//  writeReg(CONFIG, buffr, 1);
//  readReg(CONFIG, buffr, 1);
//  Serial.println(*buffr, BIN);

}

void loop() {

//  uint8_t d = 0;
//  uint8_t* buf = &d;
//
//  readReg(PWR_MGMT_1, buf, 1);
//  Serial.print("PWR_MGMT_1: ");
//  Serial.println(*buf, BIN);
//
//  readReg(GYRO_CONFIG, buf, 1);
//  Serial.print("GYRO_CONFIG: ");
//  Serial.println(*buf, BIN);
//
//  readReg(CONFIG, buf, 1);
//  Serial.print("CONFIG: ");
//  Serial.println(*buf, BIN);

}
