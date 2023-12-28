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
    LSM_SRATE_NONE = 0,
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

typedef enum {
    LSM_FIFO_BYPASS = LSM_FIFO_MODE_BYPASS,
    LSM_FIFO_NORMAL = LSM_FIFO_MODE_STOP_WHEN_FULL,
    LSM_FIFO_CONTINUOUS = LSM_FIFO_MODE_CONTINUOUS,
    LSM_FIFO_CONT_TO_FIFO = LSM_FIFO_MODE_CONT_TO_FIFO,
    LSM_FIFO_BYPASS_TO_CONT = LSM_FIFO_MODE_BYPASS_TO_CONT,
    LSM_FIFO_BYPASS_TO_FIFO = LSM_FIFO_MODE_BYPASS_TO_FIFO
} lsm6_fifo_mode;

typedef enum {
    LSM_UNCOMPRESSED_NEVER = LSM_UNCOPTR_RATE_NONE,
    LSM_UNCOMPRESSED_8 = LSM_UNCOPTR_RATE_8,
    LSM_UNCOMPRESSED_16 = LSM_UNCOPTR_RATE_16,
    LSM_UNCOMPRESSED_32 = LSM_UNCOPTR_RATE_32
} lsm6_fifo_uncompressed;

typedef enum {
    LSM_TIMESTAMP_NEVER = LSM_DEC_TS_BATCH_NONE,
    LSM_TIMESTAMP_ALWAYS = LSM_DEC_TS_BATCH_1,
    LSM_TIMESTAMP_EVERY_8 = LSM_DEC_TS_BATCH_8,
    LSM_TIMESTAMP_EVERY_32 = LSM_DEC_TS_BATCH_32
} lsm6_fifo_timestamp;

typedef enum {
    LSM_TEMP_NEVER = LSM_DEC_TS_BATCH_NONE,
    LSM_TEMP_1_6 = LSM_ODR_T_BATCH_1_6,
    LSM_TEMP_12_5 = LSM_ODR_T_BATCH_12_5,
    LSM_TEMP_52 = LSM_ODR_T_BATCH_52
} lsm6_fifo_temprate;

class LSM6DSO32 {
    public:
        struct FIFOObject {
            lsm6_fifo_tag tag;
            union {

            } data;
        };

        LSM6DSO32();
        
        bool begin(TwoWire* i2c, i2c_addr_t address);

        bool startAccel(lsm6_accel_range range, lsm6_srate rate, bool lpf2);
        bool startGyro(lsm6_gyro_range range, lsm6_srate rate);
        bool startTimestamp();
        bool startFIFO(lsm6_fifo_mode mode = LSM_FIFO_BYPASS,
                       lsm6_srate accel_rate = LSM_SRATE_NONE,
                       lsm6_srate gyro_rate = LSM_SRATE_NONE,
                       lsm6_fifo_timestamp ts_rate = LSM_TIMESTAMP_NEVER,
                       lsm6_fifo_temprate temp_rate = LSM_TEMP_NEVER,
                       bool odrchange = false,
                       int16_t watermark = 0,
                       bool stop_on_wtm = false,
                       bool en_compression = false,
                       lsm6_fifo_uncompressed uncompress_rate = LSM_UNCOMPRESSED_NEVER);
        bool setInt1(lsm6_int1_ctrl mode);
        bool setInt2(lsm6_int2_ctrl mode);
        VectorF getAccel();
        VectorF getGyro();
        uint32_t getTimestamp();
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