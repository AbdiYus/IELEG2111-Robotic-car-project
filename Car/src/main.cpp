#include <Arduino.h>
#include <Encoder.h>

int myFunction(int x, int y);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int result = myFunction(2, 3);
  Serial.println(result);
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}