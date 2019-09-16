/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   joystick.h
 * Author: toff
 *
 * Created on 20 janvier 2017, 19:26
 */

#ifndef JOYSTICK_EVENT_H
#define JOYSTICK_EVENT_H

#include <linux/joystick.h>
#include "polldevice.h"
#include <string>

class Joystick : public PollDevice {
public:
    Joystick(char *jsX);
    virtual ~Joystick();
    
    unsigned char buttonCount();
    unsigned char axisCount();
};

#endif /* JOYSTICK_EVENT_H */

