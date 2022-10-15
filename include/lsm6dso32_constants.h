/**
 * Defined values for configuration registers of LSM6DSO32
*/

#ifndef LSM6DSO32_CONSTANTS_H
#define LSM6DSO32_CONSTANTS_H

typedef enum {
    ADDR_FUNC_CFG_ACCESS    = 0x01,
    ADDR_PIN_CTRL           = 0x02,
    ADDR_FIFO_CTRL1         = 0x07,
    ADDR_FIFO_CTRL2         = 0x08,
    ADDR_FIFO_CTRL3         = 0x09,
    ADDR_FIFO_CTRL4         = 0x0a,
    ADDR_COUNTER_BDR_REG1   = 0x0b,
    ADDR_COUNTER_BDR_REG2   = 0x0c,
    ADDR_INT1_CTRL          = 0x0d,
    ADDR_INT2_CTRL          = 0x0e,
    ADDR_WHO_AM_I           = 0x0f
} lsm6_reg_addr;



#endif // LSM6DSO32_CONSTANTS_H