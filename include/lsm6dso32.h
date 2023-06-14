#ifndef LSM6DSO32_H
#define LSM6DSO32_H

#include <lsm6dso32_constants.h>
#include <ctype.h>
#include <Wire.h>

typedef int8_t i2c_addr_t;
#define NO_ADDRESS -1

class LSM6DSO32 {
  public:
    /*
      Constructor
    */
    LSM6DSO32();
    /*
      begin(i2c addr)
      Initializes sensor on bus `i2c` with I2C address `address`; if sensor detected, return true, otherwise return false
    */
    bool begin(TwoWire* i2c, i2c_addr_t address);
    bool test();
    
  private:
    i2c_addr_t address;
    TwoWire* i2cptr;

    bool readRegisters(unsigned char *buffer, lsm6_reg_addr start, size_t nbytes);
    bool writeRegister(unsigned char value, lsm6_reg_addr regaddr);

    unsigned char getWhoAmI();
};

#endif