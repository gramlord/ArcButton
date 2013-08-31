/*
  ArcButton is a simple tactile button handler.

  Copyright 2013 Graeme Elsworthy, Arcsine Pty Ltd, graeme@arcsine.com.au
  
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.
*/

#include <Arduino.h>
#include <sys/types.h>
#include <ArcSched.h>

#ifndef _ArcButton_h
#define _ArcButton_h

#define BUTTON_STATE_UP HIGH
#define BUTTON_STATE_DOWN LOW

class ArcButton {
  public:
    void setup(uint8_t, ArcSched *);
    void loop();
    bool isPressed();
    void setButtonUpProcessor(void (*)(void *), void *);
    void setButtonDownProcessor(void (*)(void *), void *);

    // these are private, but need to be public because this is used through ArcSched
    uint8_t pin;
    ArcSched *sched;
    uint8_t state;
    bool waiting;
    void *buttonUpArg;
    void *buttonDownArg;
    void (*buttonUpProcessor)(void *);
    void (*buttonDownProcessor)(void *);
};

#endif
