/*
  wiring_digital.cpp - digital input and output functions
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2018-2019 Arduino SA

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#include "Arduino.h"
#include "pins_arduino.h"

#ifdef digitalPinToGpio

void pinMode(PinName pin, PinMode mode)
{
  pinMode(PinNameToIndex(pin), mode);
}

void pinMode(pin_size_t pin, PinMode mode)
{
  gpio_t* gpio = digitalPinToGpio(pin);
  if (gpio == NULL) {
    gpio = new gpio_t();
    digitalPinToGpio(pin) = gpio;
  }

  switch (mode) {
    case INPUT:
      gpio_init_in_ex(gpio, digitalPinToPinName(pin), PullNone);
      break;
    case OUTPUT:
      gpio_init_out(gpio, digitalPinToPinName(pin));
      break;
    case INPUT_PULLUP:
      gpio_init_in_ex(gpio, digitalPinToPinName(pin), PullUp);
      break;
    case INPUT_PULLDOWN:
      gpio_init_in_ex(gpio, digitalPinToPinName(pin), PullDown);
      break;
  }
}

void digitalWrite(PinName pin, PinStatus val)
{
  digitalWrite(PinNameToIndex(pin), val);
}

void digitalWrite(pin_size_t pin, PinStatus val)
{
  gpio_write(digitalPinToGpio(pin), (int)val);
}

PinStatus digitalRead(PinName pin)
{
  return (PinStatus)digitalRead(PinNameToIndex(pin));
}

PinStatus digitalRead(pin_size_t pin)
{
  return (PinStatus)gpio_read(digitalPinToGpio(pin));
}

#else

void pinMode(PinName pin, PinMode mode) {
}

void pinMode(pin_size_t pin, PinMode mode) {
  return pinMode((PinName)pin, mode);
}

PinStatus digitalRead(PinName pin)
{
  #warning "digitalRead always applies default pull"
  return (PinStatus)mbed::DigitalIn(pin).read();
}

PinStatus digitalRead(pin_size_t pin)
{
  return digitalRead((PinName)pin);
}

void digitalWrite(PinName pin, PinStatus val)
{
  mbed::DigitalOut(pin, (int)val);
}

void digitalWrite(pin_size_t pin, PinStatus val) {
  digitalWrite((PinName)pin, val);
}

#endif // digitalPinToGpio
