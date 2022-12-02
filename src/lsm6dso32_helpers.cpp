#include <lsm6dso32.h>

// Private functions


bool LSM6DSO32::readRegisters(unsigned char *buffer, lsm6_reg_addr start, size_t nbytes) {
    if(!i2cptr || address == NO_ADDRESS) {
        return false;
    }
    size_t bytesToGo = nbytes;
    uint32_t startPos = start;
    while(bytesToGo > 3) {
        if(i2cptr->requestFrom(address, 3, start, 1, 1) != 3) return false;
        bytesToGo -= 3;
        startPos += 3;
    }    
    if(i2cptr->requestFrom(address, bytesToGo, start, 1, 1) != bytesToGo) return false;
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