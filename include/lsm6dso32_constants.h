/**
 * Defined values for configuration registers of LSM6DSO32
*/

#ifndef LSM6DSO32_CONSTANTS_H
#define LSM6DSO32_CONSTANTS_H

typedef enum {
    LSM_I2C_LO              = 0x6A,
    LSM_I2C_HI              = 0x6B
} lsm6_i2c_addr;

#define LSM_WHOAMI_ID       0x6C

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
    LSM_FUNC_CFG_ACCESS_EN          = (1 << 7),
    LSM_SHUB_REG_ACCESS_EN          = (1 << 6)
} lsm6_func_cfg_access;

typedef enum {
    LSM_SDO_PU_EN                   = 0b01111111,
    LSB_SDO_PU_DIS                  = 0b00111111
} lsm6_pin_ctrl;

typedef enum {
    LSM_STOP_ON_WTM                 = (1 << 7),
    LSM_FIFO_COMPR_RT_EN            = (1 << 6),
    LSM_ODRCHG_EN                   = (1 << 4),
    
    LSM_UNCOPTR_RATE_NONE           = (0b00 << 1),
    LSM_UNCOPTR_RATE_8              = (0b01 << 1),
    LSM_UNCOPTR_RATE_16             = (0b10 << 1),
    LSM_UNCOPTR_RATE_32             = (0b11 << 1),

    LSM_WTM8                        = (1 << 0)
} lsm6_fifo_ctrl2;

typedef enum {
    LSM_BDR_GY_NONE                 = (0b0000 << 4),
    LSM_BDR_GY_12_5                 = (0b0001 << 4),
    LSM_BDR_GY_26                   = (0b0010 << 4),
    LSM_BDR_GY_52                   = (0b0011 << 4),
    LSM_BDR_GY_104                  = (0b0100 << 4),
    LSM_BDR_GY_208                  = (0b0101 << 4),
    LSM_BDR_GY_417                  = (0b0110 << 4),
    LSM_BDR_GY_833                  = (0b0111 << 4),
    LSM_BDR_GY_1667                 = (0b1000 << 4),
    LSM_BDR_GY_3333                 = (0b1001 << 4),
    LSM_BDR_GY_6667                 = (0b1010 << 4),
    LSM_BDR_GY_6_5                  = (0b1011 << 4),

    LSM_BDR_XL_NONE                 = 0b0000,
    LSM_BDR_XL_12_5                 = 0b0001,
    LSM_BDR_XL_26                   = 0b0010,
    LSM_BDR_XL_52                   = 0b0011,
    LSM_BDR_XL_104                  = 0b0100,
    LSM_BDR_XL_208                  = 0b0101,
    LSM_BDR_XL_417                  = 0b0110,
    LSM_BDR_XL_833                  = 0b0111,
    LSM_BDR_XL_1667                 = 0b1000,
    LSM_BDR_XL_3333                 = 0b1001,
    LSM_BDR_XL_6667                 = 0b1010,
    LSM_BDR_XL_1_6                  = 0b1011
} lsm6_fifo_ctrl3;

typedef enum {
    LSM_DEC_TS_BATCH_NONE           = (0b00 << 6),
    LSM_DEC_TS_BATCH_1              = (0b01 << 6),
    LSM_DEC_TS_BATCH_8              = (0b10 << 6),
    LSM_DEC_TS_BATCH_32             = (0b11 << 6),

    LSM_ODR_T_BATCH_NONE            = (0b00 << 4),
    LSM_ODR_T_BATCH_1_6             = (0b01 << 4),
    LSM_ODR_T_BATCH_12_5            = (0b01 << 4),
    LSM_ODR_T_BATCH_52              = (0b01 << 4),

    LSM_FIFO_MODE_BYPASS            = 0b000,
    LSM_FIFO_MODE_STOP_WHEN_FULL    = 0b001,
    LSM_FIFO_MODE_CONT_TO_FIFO      = 0b011,
    LSM_FIFO_MODE_BYPASS_TO_CONT    = 0b100,
    LSM_FIFO_MODE_CONTINUOUS        = 0b110,
    LSM_FIFO_MODE_BYPASS_TO_FIFO    = 0b111
} lsm6_fifo_ctrl4;

typedef enum {
    LSM_DATAREADY_PAUSED            = 1 << 7,
    LSM_RST_COUNTER_BDR             = 1 << 6,
    LSM_TRIG_COUNTER_BDR            = 1 << 5,
    LSM_CNT_BDR_TH_3MSB             = 0b111
} lsm6_counter_bdr_reg1;

typedef enum {
    LSM_DEN_DRDY_FLAG               = 1 << 7,
    LSM_INT1_CNT_BDR                = 1 << 6,
    LSM_INT1_FIFO_FULL              = 1 << 5,
    LSM_INT1_FIFO_OVR               = 1 << 4,
    LSM_INT1_FIFO_TH                = 1 << 3,
    LSM_INT1_BOOT                   = 1 << 2,
    LSM_INT1_DRDY_G                 = 1 << 1,
    LSM_INT1_DRDY_XL                = 1 << 0
} lsm_int1_ctrl;

typedef enum {
    LSM_INT2_CNT_BDR                = 1 << 6,
    LSM_INT2_FIFO_FULL              = 1 << 5,
    LSM_INT2_FIFO_OVR               = 1 << 4,
    LSM_INT2_FIFO_TH                = 1 << 3,
    LSM_INT2_DRDY_TEMP              = 1 << 2,
    LSM_INT2_DRDY_G                 = 1 << 1,
    LSM_INT2_DRDY_XL                = 1 << 0
} lsm_int2_ctrl;

typedef enum {
    LSM_ODR_XL_POWERDOWN            = 0b0000 << 4,
    LSM_ODR_XL_1_6_HM1              = 0b1011 << 4,
    LSM_ODR_XL_12_5                 = 0b0001 << 4,
    LSM_ODR_XL_26                   = 0b0010 << 4,
    LSM_ODR_XL_52                   = 0b0011 << 4,
    LSM_ODR_XL_104                  = 0b0100 << 4,
    LSM_ODR_XL_208                  = 0b0101 << 4,
    LSM_ODR_XL_416                  = 0b0110 << 4,
    LSM_ODR_XL_833                  = 0b0111 << 4,
    LSM_ODR_XL_1_66K                = 0b1000 << 4,
    LSM_ODR_XL_3_33K                = 0b1001 << 4,
    LSM_ODR_XL_6_66K                = 0b1010 << 4,

    LSM_FS_XL_4G                    = 0b00 << 2,
    LSM_FS_XL_32G                   = 0b01 << 2,
    LSM_FS_XL_8G                    = 0b10 << 2,
    LSM_FS_XL_16G                   = 0b11 << 2,

    LSM_LPF2_XL_EN                  = 0b1 << 1
} lsm_ctrl1_xl;

typedef enum {
    LSM_ODR_G_POWERDOWN             = 0b0000 << 4,
    LSM_ODR_G_12_5                  = 0b0001 << 4,
    LSM_ODR_G_26                    = 0b0010 << 4,
    LSM_ODR_G_52                    = 0b0011 << 4,
    LSM_ODR_G_104                   = 0b0100 << 4,
    LSM_ODR_G_208                   = 0b0101 << 4,
    LSM_ODR_G_416                   = 0b0110 << 4,
    LSM_ODR_G_833                   = 0b0111 << 4,
    LSM_ODR_G_1_66K                 = 0b1000 << 4,
    LSM_ODR_G_3_33K                 = 0b1001 << 4,
    LSM_ODR_G_6_66K                 = 0b1010 << 4,

    LSM_FS_G_125                    = 0b001 << 1,
    LSM_FS_G_250                    = 0b000 << 1,
    LSM_FS_G_500                    = 0b010 << 1,
    LSM_FS_G_1000                   = 0b100 << 1,
    LSM_FS_G_2000                   = 0b110 << 1
} lsm_ctrl2_g;

typedef enum {
    LSM_XL_ULP_EN                   = 1 << 7,

    LSM_ROUNDING_NONE               = 0b00 << 5,
    LSM_ROUNDING_ACCEL              = 0b01 << 5,
    LSM_ROUNDING_GYRO               = 0b10 << 5,
    LSM_ROUNDING_BOTH               = 0b11 << 5,

    LSM_ST_G_NORMAL                 = 0b00 << 2,
    LSM_ST_G_POSITIVE               = 0b01 << 2,
    LSM_ST_G_NEGATIVE               = 0b11 << 2,

    
    LSM_ST_XL_NORMAL                = 0b00 << 0,
    LSM_ST_XL_POSITIVE              = 0b01 << 0,
    LSM_ST_XL_NEGATIVE              = 0b10 << 0
} lsm_ctrl5_c;
    // LSM_CTRL3_C             = 0x12,
    // LSM_CTRL4_C             = 0x13,
    // LSM_CTRL6_C             = 0x15,
    // LSM_CTRL7_G             = 0x16,
    // LSM_CTRL8_XL            = 0x17,
    // LSM_CTRL9_XL            = 0x18,
    // LSM_CTRL10_XL           = 0x19,
    // LSM_ALL_INT_SRC         = 0x1A,
    // LSM_TAP_SRC             = 0x1B,
    // LSM_D6D_SRC             = 0x1D,
    // LSM_STATUS_REG          = 0x1E,

    // LSM_EMB_FUNC_STATUS_MAINPAGE    = 0x35,

    // LSM_STATUS_MASTER_MAINPAGE      = 0x39,
    // LSM_FIFO_STATUS2        = 0x3B,

    // LSM_TAP_CFG0            = 0x56,
    // LSM_TAP_CFG1            = 0x57,
    // LSM_TAP_CFG2            = 0x58,
    // LSM_TAP_THS_6D          = 0x59,
    // LSM_INT_DUR2            = 0x5A,
    // LSM_WAKE_UP_THS         = 0x5B,
    // LSM_WAKE_UP_DUR         = 0x5C,
    // LSM_FREE_FALL           = 0x5D,
    // LSM_MD1_CFG             = 0x5E,
    // LSM_MD2_CFG             = 0x5F,

    // LSM_I3C_BUS_AVB         = 0x62,
    // LSM_INTERNAL_FREQ_FINE  = 0x63,

    // LSM_FIFO_DATA_OUT_TAG   = 0x78

#endif // LSM6DSO32_CONSTANTS_H