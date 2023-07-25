/**
 * Rose Rocketry LSM6DSO32 Library - Orientation dead reckoning example
 * 
 * Integrates gyroscope data to estimate current orientation. Outputs the dot
 * product of the up-direction vector at startup and the same vector rotated to
 * world space; if the sensor is in its initial orientation, the value reported
 * should be nearly 1.
 * 
 * NOTE: On PlatformIO and some other compilers, the printf/scanf %f flag is disabled by default to save memory. On
 * those platforms, the compiler flags _printf_float and _scanf_float are required for this code to output correctly.
 * 
 * Schematic:
 * STM32F411CEU6       LSM6DSO32
 * PB7 <=============> SDA
 * PB6 <=============> SCL
 * PA3 <=============> INT1
*/

#include <Arduino.h>
#include <lsm6dso32.h>

#define P_SDA   PB7
#define P_SCL   PB6

#define INT_IMU digitalPinToInterrupt(PA3)

TwoWire i2c;
LSM6DSO32 lsm;

volatile bool dataReady = false;

unsigned long lastMicros;
unsigned long currentMicros;
VectorF updir;
QuatF state;

void onInterrupt() {
    dataReady = true;
    currentMicros = micros();
}

void setup() {
    pinMode(PC13, OUTPUT);
    
    i2c.setSDA(P_SDA);  
    i2c.setSCL(P_SCL);
    i2c.setClock(400000);
    
    i2c.begin();

    if(!lsm.begin(&i2c, LSM_I2C_LO)) {
        while(1) {
            digitalToggle(PC13);
            delay(100);
        }
    }
    
    Serial.begin(4e6);
    while(!Serial);

    attachInterrupt(INT_IMU, onInterrupt, RISING);
    lsm.setInt1(LSM_INT1_DRDY_G);
    lsm.startAccel(LSM_RANGE_4G, LSM_SRATE_104, false);
    lsm.startGyro(LSM_RANGE_2000DS, LSM_SRATE_3332);

    updir = lsm.getAccel().normalize();
    state = QuatF(1, 0, 0, 0);
    lastMicros = micros();
}


void loop() {
    unsigned long tick = currentMicros - lastMicros;
    lastMicros = currentMicros;
    state = QuatF::fromAngleAxis(lsm.getGyro() * (0.000001 * tick)) * state;
    VectorF newup = updir.rotate(~state);
    Serial.printf("Dot product = %f\n", newup.dot(updir));
    while(!dataReady) { digitalWrite(PC13, HIGH); }
    dataReady = false;
    digitalWrite(PC13, LOW);
}