#include "MKHC595.h"

/**
 * Constructor for MKHC595 class.
 * Initializes data, clock, and latch pins and calls init function.
 *
 * @param dataPin   Pin for data
 * @param latchPin  Pin for latch
 * @param clockPin  Pin for clock
 */
template <uint8_t size>
MKHC595<size>::MKHC595(const uint8_t dataPin, const uint8_t latchPin,
                       const uint8_t clockPin)
    : _dataPin(dataPin), _latchPin(latchPin), _clockPin(clockPin) {
  pinMode(_dataPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_latchPin, OUTPUT);

  digitalWrite(_latchPin, LOW);
  digitalWrite(_dataPin, LOW);
  digitalWrite(_clockPin, LOW);
}

/**
 * Update function for MKHC595 class.
 * Updates the shift register with data stored in _data array.
 */
template <uint8_t size>
void MKHC595<size>::update() {
  digitalWrite(_latchPin, LOW);

  for (uint8_t i = size; i > 0; i--) {
    uint8_t temp = _data[i - 1];
    for (uint8_t j = 0; j < 8; j++) {
      digitalWrite(_dataPin, !!(temp & (1 << (7 - j))));
      digitalWrite(_clockPin, HIGH);
      digitalWrite(_clockPin, LOW);
    }
  }

  digitalWrite(_latchPin, HIGH);
  digitalWrite(_latchPin, LOW);
}

/**
 * Operator overload for MKHC595 class.
 * Returns an HC595_PIN object corresponding to the specified pin.
 *
 * @param pin Pin number
 */
template <uint8_t size>
MKHC595_PIN<size> MKHC595<size>::operator[](const unsigned int pin) {
  return MKHC595_PIN<size>(this, pin);
}

/**
 * Getter function for MKHC595 class.
 * Returns a reference to the _data array.
 */
template <uint8_t size>
uint8_t* MKHC595<size>::get(void) {
  return _data;
}

/**
 * Get function for MKHC595 class.
 * Retrieves the value of a specific pin in the shift register.
 *
 * @param pin Pin number to retrieve the value from
 * @return Value of the specified pin (0 or 1)
 */
template <uint8_t size>
uint8_t MKHC595<size>::get(unsigned int pin) {
  uint8_t byteIndex = pin / 8;
  if (byteIndex >= size) {
    return 0;
  }

  return (_data[byteIndex] >> (pin % 8)) & 1;
}

/**
 * Set function for MKHC595 class.
 * Sets the value of a specific pin in the shift register.
 *
 * @param pin     Pin number to set the value for
 * @param value   Value to set (0 or 1)
 * @param update  Flag indicating whether to update the shift register after
 * setting
 */
template <uint8_t size>
void MKHC595<size>::setAs(const uint8_t* data, bool update) {
  memcpy(_data, data, size);

  if (update) {
    this->update();
  }
}

/**
 * Toggle function for MKHC595 class.
 * Toggles the state of a specific pin in the shift register.
 *
 * @param pin     Pin number to toggle the state for
 * @param update  Flag indicating whether to update the shift register after
 * toggling
 */
template <uint8_t size>
void MKHC595<size>::toggle(unsigned int pin, bool update) {
  uint8_t byteIndex = pin / 8;
  if (byteIndex >= size) {
    return;
  }

  uint8_t bitMask = 1 << (pin % 8);
  _data[byteIndex] ^= bitMask;

  if (update) {
    this->update();
  }
}

/**
 * Toggle all ports function for MKHC595 class.
 * Toggles the state of all ports in the shift register.
 *
 * @param update  Flag indicating whether to update the shift register after
 * toggling
 */
template <uint8_t size>
void MKHC595<size>::toggleAll(bool update) {
  for (uint8_t i = 0; i < size; i++) {
    _data[i] ^= 0xFF;
  }

  if (update) {
    this->update();
  }
}

/**
 * Set all port value function for MKHC595 class.
 * Sets the value for all ports in the shift register to the specified value.
 *
 * @param value   Value to set for all ports
 * @param update  Flag indicating whether to update the shift register after
 * setting
 */
template <uint8_t size>
void MKHC595<size>::set(unsigned int pin, uint8_t value, bool update) {
  uint8_t byteIndex = pin / 8;
  if (byteIndex >= size) {
    return;
  }

  uint8_t bitMask = 1 << (pin % 8);
  if (value) _data[byteIndex] |= bitMask;
  else _data[byteIndex] &= ~bitMask;

  if (update) {
    this->update();
  }
}

/**
 * Set port value function for MKHC595 class.
 * Sets the value for a specific port in the shift register.
 *
 * @param index   Port index to set the value for
 * @param value   Value to set for the specified port
 * @param update  Flag indicating whether to update the shift register after
 * setting
 */
template <uint8_t size>
void MKHC595<size>::setPortValue(uint8_t index, uint8_t value, bool update) {
  if (index < size) {
    _data[index] = value;

    if (update) {
      this->update();
    }
  }
}

/**
 * Set all port value function for MKHC595 class.
 * Sets the value for all ports in the shift register to the specified value.
 *
 * @param value   Value to set for all ports
 * @param update  Flag indicating whether to update the shift register after
 * setting
 */
template <uint8_t size>
void MKHC595<size>::setAllValue(uint8_t value, bool update) {
  for (uint8_t i = 0; i < size; i++) {
    _data[i] = value;
  }

  if (update) {
    this->update();
  }
}

/**
 * Move function for MKHC595 class.
 * Functionality to move the content of the shift register; implementation
 * needed.
 *
 * @param step    Number of steps to move
 * @param update  Flag indicating whether to update the shift register after
 * moving
 */
template <uint8_t size>
void MKHC595<size>::move(unsigned int step, bool update) {
  if (step >= size * 8) {
    // If shift exceeds total bits, result is zero
    for (size_t i = 0; i < size; i++) {
      _data[i] = 0;
    }
    return;
  }

  // Shift by bytes
  size_t byte_shift = step / 8;
  uint8_t bit_shift = step % 8;

  if (byte_shift > 0) {
    // Move whole bytes
    for (size_t i = size - 1; i >= byte_shift; i--) {
      _data[i] = _data[i - byte_shift];
    }
    // Fill high bytes with zero
    for (size_t i = 0; i < byte_shift; i++) {
      _data[i] = 0;
    }
  }

  if (bit_shift > 0) {
    // Shift bits within bytes
    for (size_t i = size - 1; i > 0; i--) {
      _data[i] = (_data[i] >> bit_shift) | (_data[i - 1] << (8 - bit_shift));
    }
    _data[0] >>= bit_shift;
  }

  if (update) {
    this->update();
  }
}

/**
 * Constructor for HC595_PIN class.
 * Initializes HC595_PIN object with the specified HC595 object and pin number.
 *
 * @param other HC595 object reference
 * @param pin   Pin number for the HC595_PIN object
 */
template <uint8_t size>
inline MKHC595_PIN<size>::MKHC595_PIN(MKHC595<size>* other, unsigned int pin)
    : _hc595(other), _pin(pin) {}

/**
 * Overloaded assignment operator for HC595_PIN class.
 * Sets the status of the pin in the HC595 object through the HC595_PIN object.
 *
 * @param status Value to set for the pin
 * @return HC595_PIN object reference
 */
template <uint8_t size>
MKHC595_PIN<size>& MKHC595_PIN<size>::operator=(const uint8_t status) {
  _hc595->set(_pin, status);

  return *this;
}
