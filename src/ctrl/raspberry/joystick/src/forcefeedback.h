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

#ifndef FORCE_FEEDBACK_H
#define FORCE_FEEDBACK_H

#include "polldevice.h"
#include <linux/joystick.h>
#include <poll.h>
#include <string>

class ForceFeedback : public PollDevice
{
	public:
		ForceFeedback(const std::string &);
		virtual ~ForceFeedback();

		virtual void doEffect();
		virtual int32_t effectCount();

		virtual int32_t write(uint8_t *, int32_t);
		virtual int32_t read(uint8_t *, int32_t);

	private:
		struct ff_effect effects;
};

#endif /* FORCE_FEEDBACK_H */

