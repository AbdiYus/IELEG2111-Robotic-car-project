#ifndef BME280_H
#define BME280_H

#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

extern Adafruit_BME280 bme;

void bme280_init();
void print_values(float temp, float hum);
#endif
