/*
 *   Copyright (C) 2022 David G. Sparks
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "ButtonStuff.h"

// Create an array of pushbutton objects
// Note: this demo will use only one of the objects in the array
PushButton button[5];

// Connect a pushbutton to Arduino pin 3 and to ground
uint8_t buttonPin = 3;

void setup() {

  pinMode(buttonPin, INPUT_PULLUP); // pin will be HIGH when button is NOT pressed down
  pinMode(13, OUTPUT); // use onboard LED to signal operation
  digitalWrite(13, LOW); // begin with the LED turned off

}

void loop() {
  // Poll button pins repeatedly and repeatedly.
  // After a pin first changes value, i.e. 0 to 1 or 1 to 0, 
  // it takes a minimum of 12 passes through the loop, 
  // finding a consistent value, before the pin's value
  // is accepted to be stable.
  button[0].debounce(&PIND, PIND3); // pin 3 port and bit position, per datasheet
  // The button object will always return 
  // its most recently accepted stable value.
  digitalWrite(13, button[0].getBit());
  
  delay(1); // The delay need not be long, because
  // debouncing is determined by a series of consistent values, 
  // not by time. A delay might even be unnecessary. I'm not sure.
}
