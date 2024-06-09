#pragma once

#include <Arduino.h>

template <uint8_t size>
class MK_HC595_PIN;

template <uint8_t size>
class MK_HC595 {
 public:
  MK_HC595(const uint8_t dataPin, const uint8_t latchPin,
           const uint8_t clockPin);

  void update(void);
  void toggle(unsigned int pin, bool update = true);
  void toggleAll(bool update = true);
  void move(unsigned int step, bool update = true);
  void set(unsigned int pin, uint8_t value, bool update = true);
  void setAs(const uint8_t* data, bool update = true);
  void setAllValue(uint8_t value, bool update = true);
  void setPortValue(uint8_t index, uint8_t value, bool update = true);
  inline void setAll(uint8_t value, bool update = true) {
    setAllValue(value ? 0xff : 0, update);
  }

  MK_HC595_PIN<size> operator[](const unsigned int pin);

  uint8_t* get(void);
  uint8_t get(unsigned int pin);

 private:
  uint8_t _dataPin, _latchPin, _clockPin;

  uint8_t _data[size];
};

template <uint8_t size>
class MK_HC595_PIN {
 public:
  MK_HC595_PIN(MK_HC595<size>* other, const unsigned int pin);

  MK_HC595_PIN& operator=(const uint8_t other);

  operator bool() {
    return _hc595->get(_pin);
  }

 private:
  MK_HC595<size>* _hc595;
  uint8_t _pin;
};

#include "MK_HC595.hpp"
