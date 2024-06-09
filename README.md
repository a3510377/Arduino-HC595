# Arduino-MK_HC595 Library

## Overview

The MK_HC595 library provides a simple interface for controlling shift registers such as the 74HC595 using Arduino boards. This library allows you to easily interface with shift registers to expand the number of output pins available on your Arduino.

## Installation

To use the MK_HC595 library, follow these steps:

1. Download the MK_HC595 library from [GitHub repository](https://github.com/a3510377/Arduino-MK_HC595).
2. Extract the downloaded ZIP file to the `libraries` folder in your Arduino sketchbook.

## Usage

### Constructor

```cpp
MK_HC595(const uint8_t dataPin, const uint8_t latchPin, const uint8_t clockPin);
```

- `dataPin`: Pin connected to the data input of the shift register.
- `latchPin`: Pin connected to the latch input of the shift register.
- `clockPin`: Pin connected to the clock input of the shift register.

### Methods

- `void toggle(unsigned int pin, bool update = true)`: Toggles the state of a specific pin in the shift register.
- `void toggleAll(bool update = true)`: Toggles the state of all ports in the shift register.
- `void update()`: Updates the shift register with the data stored in the `_data` array.
- `void move(unsigned int step, bool update = true)`: Moves the content of the shift register by the specified number of steps.
- `void set(unsigned int pin, uint8_t value, bool update = true)`: Sets the value of a specific pin in the shift register.
- `void setAs(const uint8_t* data, bool update = true)`: Sets the data of the shift register from an array.
- `void setAllValue(uint8_t value, bool update = true)`: Sets the value for all ports in the shift register to the specified value.
- `void setPortValue(uint8_t index, uint8_t value, bool update = true)`: Sets the value for a specific port in the shift register.

### Example

#### General Use

```cpp
#include <Arduino.h>

#include <MK_HC595.h>

// Define the pins connected to the shift register
const uint8_t dataPin = 2;
const uint8_t latchPin = 3;
const uint8_t clockPin = 4;

// Create an instance of MK_HC595
MK_HC595<1> hc595(dataPin, latchPin, clockPin);

void setup() {}

void loop() {
  // Example usage of setting a pin
  hc595.set(0, HIGH);
  hc595.set(1, LOW);
  delay(1000);
  hc595.set(0, LOW);
  hc595.set(1, HIGH);
  delay(1000);
}
```

#### Simplified Use

```cpp
#include <Arduino.h>

#include <MK_HC595.h>

// Define the pins connected to the shift register
const uint8_t dataPin = 2;
const uint8_t latchPin = 3;
const uint8_t clockPin = 4;

// Create an instance of MK_HC595
MK_HC595<1> hc595(dataPin, latchPin, clockPin);

void setup() {}

void loop() {
  hc595[0] = HIGH;
  delay(1000);
  hc595[0] = LOW;
  delay(1000);
}
```

#### Toggle All

```cpp
#include <Arduino.h>

#include <MK_HC595.h>

// Define the pins connected to the shift register
const uint8_t dataPin = 2;
const uint8_t latchPin = 3;
const uint8_t clockPin = 4;

// Create an instance of MK_HC595
MK_HC595<1> hc595(dataPin, latchPin, clockPin);

void setup() {}

void loop() {
  // Toggle all ports
  hc595.toggleAll();
  delay(1000);  // Delay for 1 second
}
```

## License

This library is licensed under the [MIT License](LICENSE).
