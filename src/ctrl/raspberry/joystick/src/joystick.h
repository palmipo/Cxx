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

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_JOYSTICK_DLL
#define JOYSTICK_DLL __declspec(dllexport)
#else
#define JOYSTICK_DLL __declspec(dllimport)
#endif
#else
#define JOYSTICK_DLL
#endif

#include "polldevice.h"
#include <linux/joystick.h>
#include <poll.h>
#include <string>

class JOYSTICK_DLL Joystick : public PollDevice
{
	public:
		Joystick(const std::string & jsX);
		virtual ~Joystick();

		virtual int32_t actionIn();
		virtual int32_t actionOut();
		virtual int32_t actionError();

		virtual int32_t write(uint8_t *, int32_t);
		virtual int32_t read(uint8_t *, int32_t);

		virtual uint32_t buttonCount();
		virtual uint32_t axisCount();
};

#endif /* JOYSTICK_H */

