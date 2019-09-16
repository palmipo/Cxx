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

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <linux/joystick.h>
#include <poll.h>
#include <string>

class Joystick {
public:
    Joystick(char *jsX, char *eventXX);
    virtual ~Joystick();
    
    void doEffect();
    void scrute(int timeout=10);
    
    void setButtonCallback(void (*callback)(unsigned char, short, void *), void * =0);
    void setAxisCallback(void (*callback)(unsigned char, short, void *), void * =0);

    unsigned char buttonCount();
    unsigned char axisCount();
    int effectCount();

private:
    pollfd fds[2];
    struct ff_effect effects;
    void *_button_param, *_axis_param;
    void (*_button_callback)(unsigned char, short, void *);
    void (*_axis_callback)(unsigned char, short, void *);
};

#endif /* JOYSTICK_H */

