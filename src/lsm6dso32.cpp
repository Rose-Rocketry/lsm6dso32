#include <lsm6dso32.h>

// public-facing functions

LSM6DSO32::LSM6DSO32() {
    i2cptr = nullptr;
    address = NO_ADDRESS;
}

bool LSM6DSO32::begin(TwoWire* i2c, i2c_addr_t addr) {
    TwoWire* oldi2c = i2cptr;
    i2c_addr_t oldaddr = address;

    i2cptr = i2c;
    address = addr;
    if(readWhoAmI() != LSM_WHOAMI_ID) {
        i2cptr = oldi2c;
        address = oldaddr;
        return false;
    }
    return writeRegister(LSM_IF_INC | LSM_SW_RESET, LSM_CTRL3_C);
}

bool LSM6DSO32::startAccel(lsm6_accel_range range, lsm6_srate rate, bool lpf2) {
    unsigned char mode = range | rate | (lpf2 ? LSM_LPF2_XL_EN : 0);
    if(!writeRegister(mode, LSM_CTRL1_XL)) {
        return false; // Only update the LSB value if the write succeeds
    }
    float range_g;
    switch(range) {
        case LSM_RANGE_4G: range_g = 4; break;
        case LSM_RANGE_8G: range_g = 8; break;
        case LSM_RANGE_16G: range_g = 16; break;
        case LSM_RANGE_32G: range_g = 32; break;
    }
    lsb_xl = (range_g * LSM_GRAV) / LSM_MAXVAL;
    return true;
}

bool LSM6DSO32::startGyro(lsm6_gyro_range range, lsm6_srate rate) {
    if(rate == LSM_SRATE_1_6) { return false; }
    unsigned char mode = range | rate;
    if(!writeRegister(mode, LSM_CTRL2_G)) {
        return false;
    }
    float range_ds;
    switch(range) {
        case LSM_RANGE_125DS: range_ds = 125; break;
        case LSM_RANGE_250DS: range_ds = 250; break;
        case LSM_RANGE_500DS: range_ds = 500; break;
        case LSM_RANGE_1000DS: range_ds = 1000; break;
        case LSM_RANGE_2000DS: range_ds = 2000; break;
    }
    lsb_g = (range_ds * LSM_DEGTORAD) / LSM_MAXVAL;
    return true;
}

bool LSM6DSO32::startTimestamp() {
    return writeRegister(LSM_TIMESTAMP_EN, LSM_CTRL10_C);    
}

bool LSM6DSO32::startFIFO(lsm6_fifo_mode mode, lsm6_srate accel_rate,
                          lsm6_srate gyro_rate, lsm6_fifo_timestamp ts_rate,
                          lsm6_fifo_temprate temp_rate, bool odrchange,
                          int16_t watermark, bool stop_on_wtm,
                          bool en_compression, lsm6_fifo_uncompressed uncompress_rate) {
    char fifoctrl[4] = {
        watermark & 0xFF,

        (stop_on_wtm ? LSM_STOP_ON_WTM : 0)
        | (en_compression ? LSM_FIFO_COMPR_RT_EN : 0)
        | (odrchange ? LSM_ODRCHG_EN : 0)
        | uncompress_rate
        | (watermark >> 8) & 1,

        gyro_rate | (accel_rate >> 4), // this is a little janky but mostly works

        ts_rate | temp_rate | mode
    };
    // TODO: we should be able to write these in one batch
    return writeRegister(fifoctrl[0], LSM_FIFO_CTRL1)
        && writeRegister(fifoctrl[1], LSM_FIFO_CTRL2)
        && writeRegister(fifoctrl[2], LSM_FIFO_CTRL3)
        && writeRegister(fifoctrl[3], LSM_FIFO_CTRL4);
}

bool LSM6DSO32::setInt1(lsm6_int1_ctrl mode) {
    return writeRegister(mode, LSM_INT1_CTRL);
}

bool LSM6DSO32::setInt2(lsm6_int2_ctrl mode) {
    return writeRegister(mode, LSM_INT2_CTRL);
}

VectorF LSM6DSO32::getAccel() {
    return readVector(LSM_OUTX_L_A, lsb_xl);
}

VectorF LSM6DSO32::getGyro() {
    return readVector(LSM_OUTX_L_G, lsb_g);
}

uint32_t LSM6DSO32::getTimestamp() {
    uint32_t x;
    if(!readRegisters((unsigned char*) &x, LSM_TIMESTAMP0, sizeof(float))) {
        return -1;
    } else {    
        return x;
    }
}

bool setAccelCalib(VectorF zeroMeas) {
    float limit = max({zeroMeas.x, zeroMeas.y, zeroMeas.z});
    return true;
}

bool setGyroCalib(VectorF zeroMeas) {
    float limit = max({zeroMeas.x, zeroMeas.y, zeroMeas.z});
    return true;
}

// private functions

bool LSM6DSO32::readRegisters(unsigned char *buffer, lsm6_reg_addr start, size_t nbytes) {
    if(!i2cptr || address == NO_ADDRESS) {
        return false;
    }
    if(i2cptr->requestFrom(address, nbytes, start, 1, 1) != nbytes) return false;
    while(i2cptr->available() < nbytes);
    return (nbytes == i2cptr->readBytes(buffer, nbytes));
}

unsigned char LSM6DSO32::readWhoAmI() {
    unsigned char who;
    if(!readRegisters(&who, LSM_WHO_AM_I, 1)) {
        return -1;
    } else {
        return who;
    }
}

bool LSM6DSO32::writeRegister(unsigned char value, lsm6_reg_addr regaddr) {
    bool success = true;
    i2cptr->beginTransmission(address);
    success = success && i2cptr->write(regaddr);
    success = success && i2cptr->write(value);
    success = (i2cptr->endTransmission() == 0) && success; // Don't short circuit here
    // TODO: What happens when this function goes wrong is sorta sketchy, will deal with it when we get there
    return success;
}

VectorF LSM6DSO32::readVector(lsm6_reg_addr addr, float lsb) {
    struct {
        int16_t x;
        int16_t y;
        int16_t z;
    } raw;

    if(!readRegisters((unsigned char*) &raw, addr, sizeof(raw))) {
        return VectorF(V_ZEROES);
    } else {
        return VectorF(raw.x * lsb, raw.y * lsb, raw.z * lsb);
    }
}