/*
  ArcButton is a simple tactile button handler.

  Copyright 2013 Graeme Elsworthy, Arcsine Pty Ltd, graeme@arcsine.com.au

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.
*/

#include <ArcButton.h>
#include <ArcSched.h>

void ArcButton::setup(uint8_t b, ArcSched *s) {
  pin = b;
  sched = s;
  buttonUpProcessor = (void (*)(void *)) 0;
  buttonDownProcessor = (void (*)(void *)) 0;

  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
  state = digitalRead(pin);
  waiting = false;
}

void ArcButton::setButtonUpProcessor(void (*up)(void *), void *arg) {
  buttonUpProcessor = up;
  buttonUpArg = arg;
}

void ArcButton::setButtonDownProcessor(void (*down)(void *), void *arg) {
  buttonDownProcessor = down;
  buttonDownArg = arg;
}

void _ArcButtonCheck(SchedFunctionDetail *fd, void *arg) {
  uint8_t stateNow;
  ArcButton *button;

  button = (ArcButton *) arg;
  stateNow = digitalRead(button->pin);
  if(stateNow != button->state) {
    if(stateNow == HIGH) {
      if(button->buttonUpProcessor != (void (*)(void *)) 0)
        (*button->buttonUpProcessor)(button->buttonUpArg);
    } else {
      if(button->buttonDownProcessor != (void (*)(void *)) 0)
        (*button->buttonDownProcessor)(button->buttonDownArg);
    }
  }
  button->state = stateNow;
  button->sched->deregister(fd);
  button->waiting = false;
}

bool ArcButton::isPressed() {
  return state == LOW ? true : false;
}

void ArcButton::loop() {
  uint8_t stateNow;
  char name[8];

  stateNow = digitalRead(pin);
  if((stateNow != state) && (! waiting)) {
    sprintf(name, "AB%02d", pin);
    (void) sched->registerFunction(_ArcButtonCheck, this, name, SchedPriorityLow, 10);
    waiting = true;
  }
}
