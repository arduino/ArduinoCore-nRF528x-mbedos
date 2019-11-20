/*
  Copyright (c) 2012 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"

#ifdef digitalPinToInterruptObj

void detachInterrupt(PinName interruptNum) {
  detachInterrupt(PinNameToIndex(interruptNum));
}

void detachInterrupt(pin_size_t interruptNum) {
  if (digitalPinToInterruptObj(interruptNum) != NULL) {
    delete digitalPinToInterruptObj(interruptNum);
  }
}

void attachInterruptParam(PinName interruptNum, voidFuncPtrParam func, PinStatus mode, void* param) {
  attachInterruptParam(PinNameToIndex(interruptNum), func, mode, param);
}

void attachInterrupt(PinName interruptNum, voidFuncPtr func, PinStatus mode) {
  attachInterruptParam(interruptNum, (voidFuncPtrParam)func, mode, NULL);
}

void attachInterruptParam(pin_size_t interruptNum, voidFuncPtrParam func, PinStatus mode, void* param) {
  detachInterrupt(interruptNum);
  mbed::InterruptIn* irq = new mbed::InterruptIn(digitalPinToPinName(interruptNum));
  if (mode == FALLING) {
    irq->fall(mbed::callback(func, param));
  } else {
    irq->rise(mbed::callback(func, param));
  }
  digitalPinToInterruptObj(interruptNum) = irq;
}

void attachInterrupt(pin_size_t interruptNum, voidFuncPtr func, PinStatus mode) {
  attachInterruptParam(interruptNum, (voidFuncPtrParam)func, mode, NULL);
}

#else

#warning "Arduino style interrupts can only be used with boards defining an Arduino pinmap"

#endif