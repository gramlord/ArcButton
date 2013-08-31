/*
  This is a simple button handler. It uses the ArcSched library to debounce
  the button. Led13 will be lit when the button is pressed, and turned off when
  the button is released.
  
  Your button must be attached to a pin (6 is ued in this sketch) on one side
  and to ground on the other. The ArcButton class used an internal pull-up resister
  on the pin. So when the pin reads HIGH the button is not pressed, and when it
  reads LOW the button has been pressed. The scheduler is used to debounce the button.
  
  Copyright 2013 Graeme Elsworthy, Arcsine Pty Ltd, graeme@arcsine.com.au
  
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.
*/

#include <ArcButton.h>
#include <ArcSched.h>

// You need an ArcButton instance for each button. Here we only have a single button.
ArcButton button;

// You only require one ArcSched instance. It can handle multiple buttons.
ArcSched sched;

// This funciton will be called when the button is pressed.
void buttonPressed(void *arg) {
  digitalWrite(13, HIGH);
}

// This funciton will be called when the button is released.
void buttonReleased(void *arg) {
  digitalWrite(13, LOW);
}

void setup() {
  // Setup led 13 ready for use.
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  // Setup the scheduler.
  sched.setup();
  
  // Setup the button. This example sketch assumes the button is on pin 6.
  button.setup(6, &sched);
  
  // Set the functions which will be called. These functions are called once
  // on a button transition, not continuously.
  button.setButtonDownProcessor(buttonPressed, (void *) 0);
  button.setButtonUpProcessor(buttonReleased, (void *) 0);
}

void loop() {
  // call both the button and scheduler loop() funcitons.
  button.loop();
  sched.loop();
}
