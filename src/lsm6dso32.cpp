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
    if(getWhoAmI() != LSM_WHOAMI_ID) {
        i2cptr = oldi2c;
        address = oldaddr;
        return false;
    }
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

unsigned char LSM6DSO32::getWhoAmI() {
    unsigned char who = -1;
    if(!readRegisters(&who, LSM_WHO_AM_I, 1)) {
        return -1;
    }
    return who;
}

bool LSM6DSO32::writeRegister(unsigned char value, lsm6_reg_addr regaddr) {
    i2cptr->beginTransmission(address);
    i2cptr->write(regaddr);
    i2cptr->write(value);
    i2cptr->endTransmission();
    return true;
}