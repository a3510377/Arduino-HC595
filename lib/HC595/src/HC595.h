#pragma once

#include <Arduino.h>

template <uint8_t size>
class HC595_PIN;

template <uint8_t size>
class HC595 {
 public:
  HC595(const uint8_t dataPin, const uint8_t latchPin, const uint8_t clockPin);

  void init(void);

  void update(void);
  void move(unsigned int step, bool update = true);
  void set(unsigned int pin, uint8_t value, bool update = true);
  void setAs(const uint8_t* data, bool update = true);
  void setAllValue(uint8_t value, bool update = true);
  void setPortValue(uint8_t index, uint8_t value, bool update = true);
  inline void setAll(uint8_t value, bool update = true) {
    setAllValue(value ? 0xff : 0, update);
  }

  HC595_PIN<size> operator[](const unsigned int pin);

  uint8_t* get(void);
  uint8_t get(unsigned int pin);

 private:
  uint8_t _dataPin, _latchPin, _clockPin;

  uint8_t _data[size];
};

template <uint8_t size>
class HC595_PIN {
 public:
  HC595_PIN(HC595<size>* other, const unsigned int pin);

  HC595_PIN* operator=(const uint8_t other);

 private:
  HC595<size>* _hc595;
  uint8_t _pin;
};

#include "HC595.hpp"
