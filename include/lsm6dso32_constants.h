/**
 * Defined values for configuration registers of LSM6DSO32
*/

#ifndef LSM6DSO32_CONSTANTS_H
#define LSM6DSO32_CONSTANTS_H

typedef enum {
    LSM_I2C_LO              = 0x6A,
    LSM_I2C_HI              = 0x6B
} lsm6_i2c_addr;

typedef enum {
    LSM_FUNC_CFG_ACCESS     = 0x01,
    LSM_PIN_CTRL            = 0x02,
    LSM_FIFO_CTRL1          = 0x07,
    LSM_FIFO_CTRL2          = 0x08,
    LSM_FIFO_CTRL3          = 0x09,
    LSM_FIFO_CTRL4          = 0x0a,
    LSM_COUNTER_BDR_REG1    = 0x0b,
    LSM_COUNTER_BDR_REG2    = 0x0c,
    LSM_INT1_CTRL           = 0x0d,
    LSM_INT2_CTRL           = 0x0e,
    LSM_WHO_AM_I            = 0x0f,
    LSM_CTRL1_XL            = 0x10,
    LSM_CTRL2_G             = 0x11,
    LSM_CTRL3_C             = 0x12,
    LSM_CTRL4_C             = 0x13,
    LSM_CTRL5_C             = 0x14,
    LSM_CTRL6_C             = 0x15,
    LSM_CTRL7_G             = 0x16,
    LSM_CTRL8_XL            = 0x17,
    LSM_CTRL9_XL            = 0x18,
    LSM_CTRL10_XL           = 0x19,
    LSM_ALL_INT_SRC         = 0x1A,
    LSM_TAP_SRC             = 0x1B,
    LSM_D6D_SRC             = 0x1D,
    LSM_STATUS_REG          = 0x1E,

    LSM_OUT_TEMP_L          = 0x20,
    LSM_OUT_TEMP_H          = 0x21,
    LSM_OUTX_L_G            = 0x22,
    LSM_OUTX_H_G            = 0x23,
    LSM_OUTY_L_G            = 0x24,
    LSM_OUTY_H_G            = 0x25,
    LSM_OUTZ_L_G            = 0x26,
    LSM_OUTZ_H_G            = 0x27,
    LSM_OUTX_L_A            = 0x28,
    LSM_OUTX_H_A            = 0x29,
    LSM_OUTY_L_A            = 0x2A,
    LSM_OUTY_H_A            = 0x2B,
    LSM_OUTZ_L_A            = 0x2C,
    LSM_OUTZ_H_A            = 0x2D,

    LSM_EMB_FUNC_STATUS_MAINPAGE    = 0x35,
    LSM_FSM_STATUS_A_MAINPAGE       = 0x36,
    LSM_FSM_STATUS_B_MAINPAGE       = 0x36,

    LSM_STATUS_MASTER_MAINPAGE      = 0x39,
    LSM_FIFO_STATUS1        = 0x3A,
    LSM_FIFO_STATUS2        = 0x3B,

    LSM_TIMESTAMP0          = 0x40,
    LSM_TIMESTAMP1          = 0x41,
    LSM_TIMESTAMP2          = 0x42,
    LSM_TIMESTAMP3          = 0x43,

    LSM_TAP_CFG0            = 0x56,
    LSM_TAP_CFG1            = 0x57,
    LSM_TAP_CFG2            = 0x58,
    LSM_TAP_THS_6D          = 0x59,
    LSM_INT_DUR2            = 0x5A,
    LSM_WAKE_UP_THS         = 0x5B,
    LSM_WAKE_UP_DUR         = 0x5C,
    LSM_FREE_FALL           = 0x5D,
    LSM_MD1_CFG             = 0x5E,
    LSM_MD2_CFG             = 0x5F,

    LSM_I3C_BUS_AVB         = 0x62,
    LSM_INTERNAL_FREQ_FINE  = 0x63,

    LSM_X_OFS_USR           = 0x73,
    LSM_Y_OFS_USR           = 0x74,
    LSM_Z_OFS_USR           = 0x75,

    LSM_FIFO_DATA_OUT_TAG   = 0x78,
    LSM_FIFO_DATA_OUT_X_L   = 0x79,
    LSM_FIFO_DATA_OUT_X_H   = 0x7A,
    LSM_FIFO_DATA_OUT_Y_L   = 0x7B,
    LSM_FIFO_DATA_OUT_Y_H   = 0x7C,
    LSM_FIFO_DATA_OUT_Z_L   = 0x7D,
    LSM_FIFO_DATA_OUT_Z_H   = 0x7E
} lsm6_reg_addr;

typedef enum {
    LSM_BIT_FUNC_CFG_ACCESS = (1 << 7),
    LSM_BIT_SHUB_REG_ACCESS = (1 << 6)
} lsm6_func_cfg_access_bit;

typedef enum {
    LSM_SDO_PU_EN           = 0b01111111,
    LSB_SDO_PU_DIS          = 0b00111111
} lsm6_pin_ctrl;

#endif // LSM6DSO32_CONSTANTS_H