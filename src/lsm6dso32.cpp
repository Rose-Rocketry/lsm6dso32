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