#ifndef MY_SERIAL_H
#define MY_SERIAL_H
#include <SoftwareSerial.h>

#define RX 10
#define TX 9

SoftwareSerial my_serial(RX, TX);
void my_serial_init();
void my_serial_transmit(float temp);
#endif // MY_SERIAL_H
