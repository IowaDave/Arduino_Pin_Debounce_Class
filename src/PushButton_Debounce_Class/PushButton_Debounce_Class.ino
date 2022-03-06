#include "ButtonStuff.h"

// PushButton * button = new PushButton[5];
PushButton button[5];

uint8_t newPin;

void setup() {
  // put your setup code here, to run once:

  pinMode(3, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

}

void loop() {
  button[0].debounce(&PIND, PIND3);
  digitalWrite(13, button[0].getBit());
  delay(1);
}
