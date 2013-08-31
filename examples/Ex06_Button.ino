/*
  This is a simple button example. It uses the ArcSched library to debounce
  the button. Led13 will be toggles on each button press, using the ArcLed library.
  This is loosly based on Ex05_Button; see it for more comments.
  
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
#include <ArcLed.h>
#include <ArcSched.h>

ArcButton button;
ArcLed led;
ArcSched sched;

void buttonReleased(void *arg) {
  // Uncomment the one that takes your fancy.
  led.toggle();
  // led.flash(50);
}

void setup() {
  // Setup the scheduler.
  sched.setup();
  led.setup(13, &sched);
  button.setup(6, &sched);
  button.setButtonUpProcessor(buttonReleased, (void *) 0);
}

void loop() {
  button.loop();
  sched.loop();
}
