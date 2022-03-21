BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/raspipia.o

UTIL_PWD = ../../util
RASPI_PWD = ../../ctrl/raspberry
POLL_PWD = ../../ctrl/raspberry/poll
GPIO_PWD = ../../ctrl/raspberry/gpio
CC = g++
MAKE = make
INCLUDE = -Isrc -I$(GPIO_PWD)/src -I$(POLL_PWD)/src -I$(UTIL_PWD)/src
LIBS = -L. -lraspigpio -lpoll

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

#
#
clean:
	$(MAKE) -C $(RASPI_PWD) $@
	rm -f $(BIN_PWD)/*.o *.so

#
#
libraspi.so:
	$(MAKE) -C $(RASPI_PWD) $@
	ln -s $(RASPI_PWD)/$@

#
#
libpia.so: $(OBJECTS) libraspi.so
	$(CC) $(CFLAGS) -shared $^ -o $@

#
#
$(BIN_PWD)/%.o: src/%.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI

