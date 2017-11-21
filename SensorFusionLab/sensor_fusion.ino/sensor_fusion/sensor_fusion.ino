#include <sensor_fusion.h>
#include <printf.h>
#include <Wire.h>

int xAccelBias,yAccelBias,zAccelBias,xGyroBias,yGyroBias,zGyroBias;

//variables for awkward online function
float angle_x, angle_y, angle_x_acc, angle_y_acc = 0;
long total_accel_vector = 0;
float angle_x_output, angle_y_output = 0;
long loop_timer = 0;

//variables for quaterion
float magnitude = 0;
float currentAngle, pastAngle, deltaAngle= 0;
float deltaTime = 0;
bool first_time_run = false;

float accelWeight = 0.5;

struct vector accel;
struct vector gyro;
struct vector filteredVect;
struct quaternion quater;
struct vector gyroOrientation;

void setup() {
  setupRegisters();  
  biasCorrect();
  //loop_timer = micros();
  deltaTime = millis();
  gyroOrientation.x = 0;
  gyroOrientation.y = 0;
  gyroOrientation.z = 1;
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

void printVector(struct vector v) {
  
  Serial.print(v.x);
  Serial.print(" ");
  Serial.print(v.y);
  Serial.print(" ");
  Serial.print(v.z);
  Serial.print(" ");
}

void loop() {
  if (getStatusReg()){
    //Serial.print("Accelerometer: ");
    updateAccelVector();
    vector_normalize(&accel,&accel);
    printVector(accel);
    //Serial.println();
    //Serial.println();
    //Serial.print("Gyro: ");
    updateGyroVector();
    //printVector(gyro);
    

    quaternionator(&gyroOrientation);
    quaternionator(&filteredVect);
    printVector(gyroOrientation);
    filterAndCombine();
    printVector(filteredVect);
    Serial.println();
    deltaTime = millis();
    
  }
}
