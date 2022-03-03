BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/raspipia.o

POLL_PWD = ../../ctrl/raspberry/poll
UTIL_PWD = ../../util
LOG_PWD = ../../ctrl/raspberry/log
GPIO_PWD = ../../ctrl/raspberry/gpio
CC = g++
MAKE = make
INCLUDE = -Isrc -I$(GPIO_PWD)/src -I$(POLL_PWD)/src -I$(UTIL_PWD)/src
LIBS = -L. -lraspigpio -lpoll -lutil

CFLAGS = -g -std=c++11 $(INCLUDE) -DRASPI -fPIC
LDFLAGS = $(LIBS)

all:

#
#
clean:
	$(MAKE) -C $(GPIO_PWD) $@
	rm -f $(BIN_PWD)/*.o *.so

#
#
libraspigpio.so:
	$(MAKE) -C $(GPIO_PWD) $@
	ln -s $(GPIO_PWD)/$@

#
#
liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

#
#
libutil.so:
	$(MAKE) -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

#
#
libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

#
#
libpia.so: $(OBJECTS) libutil.so libpoll.so libraspigpio.so
	$(CC) $(CFLAGS) -shared $^ -o $@

#
#
$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

