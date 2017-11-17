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
const int INT_STATUS = 0x3A;
const int ACCEL_XOUT_H = 0x3B;
const int ACCEL_XOUT_L = 0x3C;
const int ACCEL_YOUT_H = 0x3D;
const int ACCEL_YOUT_L = 0x3E;
const int ACCEL_ZOUT_H = 0x3F;
const int ACCEL_ZOUT_L = 0x40;

const int GYRO_XOUT_H = 0x43;
const int GYRO_XOUT_L = 0x44;
const int GYRO_YOUT_H = 0x45;
const int GYRO_YOUT_L = 0x46;
const int GYRO_ZOUT_H = 0x47;
const int GYRO_ZOUT_L = 0x48;

const int MPU_addr = 0x68;  // I2C address of the MPU-6050
