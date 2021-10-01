#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <cstring>
#include <iostream>
#include "joystick.h"
#include "joystickexception.h"
#include <sstream>
/*
 * https://www.kernel.org/doc/Documentation/input/joystick-api.txt
 */
Joystick::Joystick(const std::string & jsX)
: PollDevice()
{
	_handler = ::open(jsX.c_str(), O_RDONLY);
	if (_handler < 0)
	{
		std::stringstream ss;
		ss << "ouverture du device impossible : " << jsX;
		throw JoystickException(__FILE__, __LINE__, ss.str());
	}
}

Joystick::~Joystick()
{
	if (::close (_handler) < 0)
	{
		std::stringstream ss;
		ss << "fermeture du device impossible.";
		std::cerr << ss.str() << std::endl;
	}
}

uint32_t Joystick::axisCount()
{
	uint32_t nb_axes = 0;
	if (::ioctl(_handler, JSIOCGAXES, &nb_axes) < 0)
	{
		std::stringstream ss;
		ss << "lecture du nombre d\'axe du device impossible.";
		throw JoystickException(__FILE__, __LINE__, ss.str());
	}

	return nb_axes;
}

uint32_t Joystick::buttonCount()
{
	uint8_t nb_boutons = 0;
	if (::ioctl(_handler, JSIOCGBUTTONS, &nb_boutons) < 0)
	{
		std::stringstream ss;
		ss << "lecture du nombre de bouton du device impossible.";
		throw JoystickException(__FILE__, __LINE__, ss.str());
	}

	return nb_boutons;
}

int32_t Joystick::write(uint8_t *, int32_t)
{
	return 0;
}

int32_t Joystick::read(uint8_t * data, int32_t nb_data)
{
	struct js_event e;
	if (::read (_handler, &e, sizeof(struct js_event)) < 0)
	{
		std::stringstream ss;
		ss << "lecture des boutons du device impossible.";
		throw JoystickException(__FILE__, __LINE__, ss.str());
	}

	std::cout << "JS_EVENT_INIT type " << (int32_t)e.type << " ; number " << (int32_t)e.number << " ; value " << (int32_t)e.value << std::endl;
	// initialisation
	if ((e.type & JS_EVENT_INIT) == JS_EVENT_INIT)
	{
		return 0;
	}

	// lecture des boutons
	else
	{
		data[0] = e.type & ~JS_EVENT_INIT;
		data[1] = e.number;
		data[2] = (e.value & 0xFF00) >> 8;
		data[3] = (e.value & 0x00FF);
	}

	return 4;
}
