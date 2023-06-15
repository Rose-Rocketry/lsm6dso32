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
    return true;
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

VectorF LSM6DSO32::getAccel() {
    return readVector(LSM_OUTX_L_A, lsb_xl);
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
    unsigned char who = -1;
    if(!readRegisters(&who, LSM_WHO_AM_I, 1)) {
        return -1;
    }
    return who;
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