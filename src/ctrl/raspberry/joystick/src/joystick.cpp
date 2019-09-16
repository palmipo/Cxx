#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <cstring>
#include <iostream>
#include "joystick.h"

/*
 * https://www.kernel.org/doc/Documentation/input/joystick-api.txt
 *
 * force feedback : fftest /dev/input/event15
 * https://www.kernel.org/doc/Documentation/input/ff.txt
 */
Joystick::Joystick(char *jsX, char *eventXX)
: _button_callback(0)
, _axis_callback(0)
, _button_param(0)
, _axis_param(0)
{
    fds[0].fd = open(jsX, O_RDONLY);
    if (fds[0].fd < 0)
    {
        std::cout << "ouverture du device impossible : " << jsX << std::endl;
    }

    fds[1].fd = open(eventXX, O_RDWR);
    if (fds[1].fd < 0)
    {
        std::cout << "ouverture du device impossible : " << eventXX << std::endl;
    }

    /* download a periodic sinusoidal effect */
    memset(&effects, 0, sizeof(struct ff_effect));
    effects.type = FF_PERIODIC;
    effects.id = -1;
    effects.u.periodic.waveform = FF_SINE;
    effects.u.periodic.period = 100;	/* 0.1 second */
    effects.u.periodic.magnitude = 0x7fff;	/* 0.5 * Maximum magnitude */
    effects.u.periodic.offset = 0;
    effects.u.periodic.phase = 0;
    effects.direction = 0x4000;	/* Along X axis */
    effects.u.periodic.envelope.attack_length = 1000;
    effects.u.periodic.envelope.attack_level = 0x7fff;
    effects.u.periodic.envelope.fade_length = 1000;
    effects.u.periodic.envelope.fade_level = 0x7fff;
    effects.trigger.button = 0;
    effects.trigger.interval = 0;
    effects.replay.length = 20000;  /* 20 seconds */
    effects.replay.delay = 1000;

    if (ioctl(fds[1].fd, EVIOCSFF, &effects) < 0)
    {
        std::cout << "creation effet impossible" << std::endl;
    }
}

Joystick::~Joystick()
{
    // supprimer un effet
    ioctl(fds[1].fd, EVIOCRMFF, &effects.id);

    if (close (fds[1].fd) < 0) {
        std::cout << "fermeture du device impossible." << std::endl;
    }

    if (close (fds[0].fd) < 0) {
        std::cout << "fermeture du device impossible." << std::endl;
    }
}

unsigned char Joystick::axisCount()
{
    unsigned char nb_axes;
    if (ioctl(fds[0].fd, JSIOCGAXES, &nb_axes) < 0) {
        std::cout << "lecture du nombre d\'axe du device impossible." << std::endl;
    }
    std::cout << "nb axes " <<  (int)nb_axes << std::endl;
}

unsigned char Joystick::buttonCount()
{
    unsigned char nb_boutons;
    if (ioctl(fds[0].fd, JSIOCGBUTTONS, &nb_boutons) < 0)
    {
        std::cout << "lecture du nombre de bouton du device impossible." << std::endl;
    }
    std::cout << "nb boutons " << (int)nb_boutons << std::endl;
}

int Joystick::effectCount()
{
    int nb_effet;
    if (ioctl(fds[1].fd, EVIOCGEFFECTS, &nb_effet) < 0)
    {
        std::cout << "lecture du nombre d\'effet du device impossible." << std::endl;
    }
    std::cout << "nb effets " <<  nb_effet << " simultanes possible" << std::endl;
}

void Joystick::setButtonCallback(void (*callback)(unsigned char, short, void *), void *param)
{
    _button_callback = callback;
    _button_param = param;
}

void Joystick::setAxisCallback(void (*callback)(unsigned char, short, void *), void *param)
{
    _axis_callback = callback;
    _axis_param = param;
}

void Joystick::doEffect()
{
    struct input_event play;
    memset(&play,0,sizeof(play));
    play.type = EV_FF;
    play.code = effects.id;
    play.value = 1;

    if (write(fds[1].fd, (const void*) &play, sizeof(input_event)) < 0)
    {
        std::cout << "Play effect abort" << std::endl;
    }
}

void Joystick::scrute(int timeout)
{
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    fds[1].events = POLLIN;
    fds[1].revents = 0;

    // scrute le joystick durant 10ms
    if (0 < poll(fds, 2, timeout))
    {
        if (fds[0].revents != 0)
        {
            struct js_event e;
            if (0 < read (fds[0].fd, &e, sizeof(struct js_event)))
            {
                // initialisation
                if ((e.type & JS_EVENT_INIT) == JS_EVENT_INIT)
                {
                    std::cout << "JS_EVENT_INIT type " << (int)e.type << " ; number " << (int)e.number << " ; value " << (int)e.value << std::endl;
                }

                // lecture des boutons
                else
                {
                    //std::cout << "JS_EVENT" << std::endl;
                    if ((e.type & ~JS_EVENT_INIT) == JS_EVENT_BUTTON)
                    {
                        //std::cout << "JS_EVENT_BUTTON" << std::endl;
                        if (_button_callback)
                            _button_callback(e.number, e.value, _button_param);
                    }

                    // lecture des axes
                    else if ((e.type & ~JS_EVENT_INIT) == JS_EVENT_AXIS)
                    {
                        //std::cout << "JS_EVENT_AXIS" << std::endl;
                        if (_axis_callback)
                            _axis_callback(e.number, e.value, _axis_param);
                   }
                }
            }
        }

        if (fds[1].revents != 0)
        {
            struct input_event ie;
            if (0 < read (fds[1].fd, &ie, sizeof(struct input_event)))
            {
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
            }
        }
    }
}

