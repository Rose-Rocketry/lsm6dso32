#ifndef LSM6DSO32_H
#define LSM6DSO32_H

#include <lsm6dso32_constants.h>
#include <ctype.h>
#include <Wire.h>

#include "VectorMath.h"

typedef int8_t i2c_addr_t;
#define NO_ADDRESS -1

typedef enum {
  LSM_RANGE_4G = LSM_FS_XL_4G,
  LSM_RANGE_8G = LSM_FS_XL_8G,
  LSM_RANGE_16G = LSM_FS_XL_16G,
  LSM_RANGE_32G = LSM_FS_XL_32G
} lsm6_accel_range;

typedef enum {
  LSM_RANGE_125DS = LSM_FS_G_125,
  LSM_RANGE_250DS = LSM_FS_G_250,
  LSM_RANGE_500DS = LSM_FS_G_500,
  LSM_RANGE_1000DS = LSM_FS_G_1000,
  LSM_RANGE_2000DS = LSM_FS_G_2000
} lsm6_gyro_range;

typedef enum {
  LSM_SRATE_1_6 = LSM_ODR_XL_1_6_HM1,
  LSM_SRATE_12_5 = LSM_ODR_XL_12_5,
  LSM_SRATE_26 = LSM_ODR_XL_26,
  LSM_SRATE_52 = LSM_ODR_XL_52,
  LSM_SRATE_104 = LSM_ODR_XL_104,
  LSM_SRATE_208 = LSM_ODR_XL_208,
  LSM_SRATE_416 = LSM_ODR_XL_416,
  LSM_SRATE_833 = LSM_ODR_XL_833,
  LSM_SRATE_1666 = LSM_ODR_XL_1666,
  LSM_SRATE_3332 = LSM_ODR_XL_3332,
  LSM_SRATE_6664 = LSM_ODR_XL_6664
} lsm6_srate;

class LSM6DSO32 {
  public:
    LSM6DSO32();
    
    bool begin(TwoWire* i2c, i2c_addr_t address);

    bool startAccel(lsm6_accel_range range, lsm6_srate rate, bool lpf2);
    bool startGyro(lsm6_gyro_range range, lsm6_srate rate);
    VectorF getAccel();
    VectorF getGyro();

  private:
    i2c_addr_t address;
    TwoWire* i2cptr;

    bool readRegisters(unsigned char *buffer, lsm6_reg_addr start, size_t nbytes);
    bool writeRegister(unsigned char value, lsm6_reg_addr regaddr);

    unsigned char readWhoAmI();

    float lsb_xl, lsb_g; // Value of LSB in SI units

    VectorF readVector(lsm6_reg_addr addr, float lsb);
};

#endif