#include <Arduino.h>
#include <lsm6dso32.h>

#define P_SDA   PB7
#define P_SCL   PB6

TwoWire i2c;
LSM6DSO32 lsm;

void setup() {
    i2c.setSDA(P_SDA);
    i2c.setSCL(P_SCL);

    i2c.begin();
    lsm.begin(&i2c, LSM_I2C_LO);

    Serial.begin(9600);
    while(!Serial);

    lsm.startAccel(LSM_RANGE_4G, LSM_SRATE_104, false);
    lsm.startGyro(LSM_RANGE_125DS, LSM_SRATE_104);
}

void loop() {
    VectorF accel = lsm.getAccel();
    VectorF gyro = lsm.getGyro();
    Serial.printf("Accel <%f, %f, %f>\t", accel.x, accel.y, accel.z);
    Serial.printf("Gyro <%f, %f, %f>\n", gyro.x, gyro.y, gyro.z);
    delay(100);
}