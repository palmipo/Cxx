#include <time.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <poll.h>

#include "raspii2c.h"
#include "ada772.h"
#include "hd44780.h"
#include "gpio_irq_mod.h"

static void bouton(unsigned char value, void *user_data)
{
	try
	{
		std::cout << "bouton = " << (int)value << std::endl;
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
	}
}

int main(int argc, char **argv)
{
	int fd_irq = -1;

	if (argc < 3)
	{
		std::cout << argv[0] << " </dev/i2c-1 /dev/gpioirq0>" << std::endl;
		return -1;
	}

	try
	{
		fd_irq = open(argv[2], O_RDWR);
		if (fd_irq < 0)
		{
			std::cout << "open error" << std::endl;
			return -1;
		}

		// entree
		struct gpio_irq_ioctl ctrl;
		ctrl.cmd = GPIO_IRQ_INPUT;
		ctrl.port = 17;
		ctrl.value = 1;
		if (ioctl(fd_irq, GPIO_IRQ_RDWR, &ctrl) < 0)
		{
			std::cout << "port " << ctrl.port << " ioctl error" << std::endl;
			return -1;
		}
		std::cout << "lecture port " << ctrl.port << " : " << ctrl.value << std::endl;

		ctrl.cmd = GPIO_IRQ_INPUT | GPIO_IRQ_FALLING_INTERRUPT;
		ctrl.port = 4;
		ctrl.value = 1;
		if (ioctl(fd_irq, GPIO_IRQ_RDWR, &ctrl) < 0)
		{
			std::cout << "port " << ctrl.port << " ioctl error" << std::endl;
			return -1;
		}
		std::cout << "lecture port " << ctrl.port << " : " << ctrl.value << std::endl;

		RaspiI2C i2c(argv[1]);

		ADA772 afficheur(&i2c);
		afficheur.setBackLight(1);
		afficheur.setButtonsCallback(bouton, 0);

		std::string str_date;
		struct tm *la_date;
		long t;
		int cpt = 0;
		while (cpt < 500)
		{
			time(&t);
			la_date = localtime(&t);
			std::stringstream buf_date;
			buf_date << std::setw(2) << std::setfill('0') << la_date->tm_mday << "-" << std::setw(2) << std::setfill('0') << 1 + la_date->tm_mon << "-" << std::setw(4) << std::setfill('0') << 1900 + la_date->tm_year << " " << std::setw(2) << std::setfill('0') << la_date->tm_hour <<":" << std::setw(2) << std::setfill('0') << la_date->tm_min;
			str_date = buf_date.str();
			
			afficheur.LCD()->setPosition(0, 0);
			afficheur.LCD()->setText((s8*)str_date.c_str(), str_date.length());

			afficheur.LCD()->setPosition(1, 0);
			afficheur.LCD()->setText((s8*)"20 C", 4);
			
			struct pollfd pfd;
			pfd.fd = fd_irq;
			pfd.events = POLLIN | POLLRDNORM;
			pfd.revents = 0;
			
			if (0 < poll(&pfd, 1, 1000))
			{
				ctrl.cmd = GPIO_IRQ_INT;
				if (ioctl(fd_irq, GPIO_IRQ_RDWR, &ctrl) < 0)
				{
					std::cout << "error read" << std::endl;
				}
				std::cout << "irq : " << ctrl.port << " ; valeur : " << ctrl.value << std::endl;
				afficheur.scrute();
			}

			std::cout << "compteur : " << cpt << std::endl;
			++cpt;
		}
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
		return -1;
	}

	close(fd_irq);

	return 0;
}
