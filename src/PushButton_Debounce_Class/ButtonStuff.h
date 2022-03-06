#pragma once

#include "Arduino.h"

enum ButtonState {
  SETTLED,
  PENDING
};

class PushButton {
  
  uint8_t accepted;
  uint8_t novel;
  uint16_t debounceBits;
  ButtonState state;

  uint8_t pinBit (uint8_t * reg, const uint8_t pin) {
    if (reg == &ACSR) return ((*reg & (1 << pin)) >> pin);
    if ((reg == &PINB) | (reg == &PINC) | (reg == &PIND))
        return ! ((*reg & (1 << pin)) >> pin);
    return 0;
  }
  
  public:
  PushButton::PushButton () :
  accepted(0), novel(0), debounceBits(0), state(SETTLED)  {}

  void debounce (uint8_t reg, uint8_t pin) {
    uint8_t thisPin = this->pinBit(reg, pin);
    if (this->state == SETTLED) {
       if (this->accepted != thisPin) { 
          // pin changed from settled state and accepted status
          // save new status and establish new state
          this->novel = thisPin;
          this->state =  PENDING;
       }
    }

    if (this->state == PENDING) {
      if (thisPin != this->novel) {
        // button status changed while pending
        // save new status and remain in pending state
        this->novel = thisPin;
      }
      // advance the debounce bits a notch
      this->debounceBits =
        (this->debounceBits << 1)
        | this->novel | 0xe000;

      // check the result
      if (
        (this->debounceBits == 0xf000)
        || (this->debounceBits == 0xffff)
      ) { 
        // accept new button position
        this->accepted = this->novel;
        this->state = SETTLED;
      }
    }
  } 
  
  // report the most recently settled value   
  uint8_t PushButton::getBit () {
    return this->accepted;
  }

  ButtonState PushButton::getState() {
    return this->state;
  }

  uint16_t PushButton::getDebounceBits() {
    return this->debounceBits;
  }

};
