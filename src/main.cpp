#include <Arduino.h>
#include <HC595.h>

HC595<1> s1(10, 9, 8);

void setup() {
  Serial.begin(9600);
}

void loop() {
  uint8_t data[] = {0b10101010};
  s1.setAs(data, true);

  s1.move(1);
}
