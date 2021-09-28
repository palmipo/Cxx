#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <cstring>
#include <iostream>
#include "forcefeedback.h"

/*
 * force feedback : fftest /dev/input/event15
 * https://www.kernel.org/doc/Documentation/input/ff.txt
 */
ForceFeedback::ForceFeedback(const std::string & eventXX)
: PollDevice()
{
    _handler = ::open(eventXX.c_str(), O_RDWR);
    if (_handler < 0)
    {
        std::cout << "ouverture du device impossible : " << eventXX << std::endl;
    }

    /* download a periodic sinusoidal effect */
    // memset(&effects, 0, sizeof(struct ff_effect));
    // effects.type = FF_PERIODIC;
    // effects.id = -1;
    // effects.u.periodic.waveform = FF_SINE;
    // effects.u.periodic.period = 100;	/* 0.1 second */
    // effects.u.periodic.magnitude = 0x7fff;	/* 0.5 * Maximum magnitude */
    // effects.u.periodic.offset = 0;
    // effects.u.periodic.phase = 0;
    // effects.direction = 0x4000;	/* Along X axis */
    // effects.u.periodic.envelope.attack_length = 1000;
    // effects.u.periodic.envelope.attack_level = 0x7fff;
    // effects.u.periodic.envelope.fade_length = 1000;
    // effects.u.periodic.envelope.fade_level = 0x7fff;
    // effects.trigger.button = 0;
    // effects.trigger.interval = 0;
    // effects.replay.length = 20000;  /* 20 seconds */
    // effects.replay.delay = 1000;

    // if (::ioctl(_handler, EVIOCSFF, &effects) < 0)
    // {
        // std::cout << "creation effet impossible" << std::endl;
    // }
}

ForceFeedback::~ForceFeedback()
{
    /* supprimer un effet */
    ::ioctl(_handler, EVIOCRMFF, &effects.id);

    if (::close (_handler) < 0) {
        std::cout << "fermeture du device impossible." << std::endl;
    }
}

int32_t ForceFeedback::effectCount()
{
    int32_t nb_effet = 0;
    if (::ioctl(_handler, EVIOCGEFFECTS, &nb_effet) < 0)
    {
        std::cout << "lecture du nombre d\'effet du device impossible." << std::endl;
    }

    return nb_effet;
}

void ForceFeedback::doEffect()
{
    struct input_event play;
    play.type = EV_FF;
    play.code = effects.id;
    play.value = 1;

    if (::write(_handler, (const void*) &play, sizeof(input_event)) < 0)
    {
        std::cout << "Play effect abort" << std::endl;
    }
}

int32_t ForceFeedback::write(uint8_t *, int32_t)
{
	return 0;
}

int32_t ForceFeedback::read(uint8_t *, int32_t)
{
	struct input_event ie;
	if (::read (_handler, &ie, sizeof(struct input_event)) < 0)
	{
	}
	
	std::cout << "type " << ie.type << " ; code " << ie.code << " ; value " << ie.value << std::endl;
	/*
		switch(ie.type)
		{
			case 1:
						if (_button_callback)
							_button_callback(ie.code, ie.value, _button_param);
				break;
			
			case 3:
						 if (_axis_callback)
							_axis_callback(ie.code, ie.value, _axis_param);
				break;
		}
		*/
	return 0;
}
