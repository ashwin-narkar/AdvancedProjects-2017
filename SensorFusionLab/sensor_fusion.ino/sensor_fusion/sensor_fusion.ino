#include <sensor_fusion.h>
#include <printf.h>
#include <Wire.h>

int xAccelBias,yAccelBias,zAccelBias,xGyroBias,yGyroBias,zGyroBias;

struct vect {
  int x;
  int y;
  int z;
};

struct vect accel;
struct vect gyro;

void setup() {
  setupRegisters();  
  biasCorrect();
}

void updateAccelVector() {
  accel.x = getAccelX()-xAccelBias;
  accel.y = getAccelY()-yAccelBias;
  accel.z = getAccelZ()-zAccelBias;
}

void updateGyroVector() {
  gyro.x = getGyroX()-xGyroBias;
  gyro.y = getGyroY()-yGyroBias;
  gyro.z = getGyroZ()-zGyroBias;
}

void printVector(struct vect v) {
  
  Serial.print(v.x);
  Serial.print(" ");
  Serial.print(v.y);
  Serial.print(" ");
  Serial.println(v.z);
  
}

void loop() {
  if (getStatusReg()){
    //Serial.print("Accelerometer: ");
    updateAccelVector();
    printVector(accel);
    //Serial.println();
    //Serial.println();
    //Serial.print("Gyro: ");
    //updateGyroVector();
    //printVector(gyro);
    //delay(1000);
  }
}
