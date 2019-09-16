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
Joystick::Joystick(char *jsX)
: _button_callback(0)
, _axis_callback(0)
, _button_param(0)
, _axis_param(0)
{
    fds.fd = open(jsX, O_RDONLY);
    if (fds.fd < 0)
    {
        std::cout << "ouverture du device impossible : " << jsX << std::endl;
    }
}

Joystick::~Joystick()
{
    if (close (fds.fd) < 0) {
        std::cout << "fermeture du device impossible." << std::endl;
    }
}

unsigned char Joystick::axisCount()
{
    unsigned char nb_axes;
    if (ioctl(fds.fd, JSIOCGAXES, &nb_axes) < 0) {
        std::cout << "lecture du nombre d\'axe du device impossible." << std::endl;
    }
    std::cout << "nb axes " <<  (int)nb_axes << std::endl;
}

unsigned char Joystick::buttonCount()
{
    unsigned char nb_boutons;
    if (ioctl(fds.fd, JSIOCGBUTTONS, &nb_boutons) < 0)
    {
        std::cout << "lecture du nombre de bouton du device impossible." << std::endl;
    }
    std::cout << "nb boutons " << (int)nb_boutons << std::endl;
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

void Joystick::scrute(int timeout)
{
    pollfd fds;
    fds.events = POLLIN;
    fds.revents = 0;

    // scrute le joystick durant 10ms
    if (0 < poll(&fds, 1, timeout))
    {
        if (fds.revents != 0)
        {
            struct js_event e;
            if (0 < read (fds.fd, &e, sizeof(struct js_event)))
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
    }
}
