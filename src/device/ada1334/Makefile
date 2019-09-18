OBJECTS = \
	bin/ada1334.o

LOG_PWD = ../../ctrl/raspberry/log
POLL_PWD = ../../ctrl/raspberry/factory
I2C_PWD = ../../ctrl/raspberry/i2c
I2CDEV_PWD = ../i2c
GPIO_PWD = ../../ctrl/raspberry/gpio

CC = g++
MAKE = make
INCLUDE = -I../../ctrl/interface -Isrc -I$(LOG_PWD)/src -I$(POLL_PWD)/src -I$(I2C_PWD)/src -I$(I2CDEV_PWD)/src -I$(GPIO_PWD)/src
LIBS = -L. -llog -lpoll -lraspii2c -li2cdevice -lgpio -lada1334

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

#
#
clean:
	$(MAKE) -C $(LOG_PWD) $@
	$(MAKE) -C $(POLL_PWD) $@
	$(MAKE) -C $(I2C_PWD) $@
	$(MAKE) -C $(I2CDEV_PWD) $@
	$(MAKE) -C $(GPIO_PWD) $@
	rm -f bin/*.o *.so lumiere

#
##
lumiere: bin/lumiere.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) libraspii2c.so
	$(MAKE) libi2cdevice.so
	$(MAKE) libgpio.so
	$(MAKE) libada1334.so
	$(CC) -o $@ $^ $(LDFLAGS)

bin/lumiere.o: test/lumiere.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

#
#
libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

#
#
libraspii2c.so:
	$(MAKE) -C $(I2C_PWD) $@
	ln -s $(I2C_PWD)/$@

#
#
libi2cdevice.so:
	$(MAKE) -C $(I2CDEV_PWD) $@
	ln -s $(I2CDEV_PWD)/$@

#
#
libgpio.so:
	$(MAKE) -C $(GPIO_PWD) $@
	ln -s $(GPIO_PWD)/$@

#
#
libada1334.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared $^ -o $@

#
#
bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
