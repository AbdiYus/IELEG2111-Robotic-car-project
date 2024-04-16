#include "bme280.h"
Adafruit_BME280 bme;

void bme280_init() {
  if (!bme.begin(0x77)) {
    Serial.println("Kunne ikke tilkoble BME280!");
    while (1)
      ;
  }
}

void print_values(float temp, float hum) {
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println("*C");

  Serial.print("Humidity = ");
  Serial.print(hum);
  Serial.println("%");
}