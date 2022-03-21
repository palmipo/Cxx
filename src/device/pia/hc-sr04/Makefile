BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/hc_sr04.o

UTIL_PWD = ../../../util
PIA_PWD = ../
RASPI_PWD = ../../../ctrl/raspberry
POLL_PWD = $(RASPI_PWD)/poll
GPIO_PWD = $(RASPI_PWD)/gpio
CC = g++
MAKE = make
INCLUDE = -Isrc -I$(POLL_PWD)/src -I$(GPIO_PWD)/src -I$(UTIL_PWD)/src -I$(PIA_PWD)/src
LIBS = -L. -lpia -lraspi

CFLAGS = -g -std=c++11 $(INCLUDE) -DRASPI -fPIC
LDFLAGS = $(LIBS) -lpthread

all:

#
#
clean:
	$(MAKE) -C $(RASPI_PWD) $@
	$(MAKE) -C $(PIA_PWD) $@
	rm -f $(BIN_PWD)/*.o *.so

#
#
telemetre: $(BIN_PWD)/test_telemetre.o libraspi.so libpia.so libhcsr04.so libhcsr04.so
	$(CC) -o $@ $< $(LDFLAGS) -lhcsr04

$(BIN_PWD)/test_telemetre.o: test/test_telemetre.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
#
libraspi.so:
	$(MAKE) -C $(RASPI_PWD) $@
	ln -s $(RASPI_PWD)/$@

#
#
libpia.so:
	$(MAKE) -C $(PIA_PWD) $@
	ln -s $(PIA_PWD)/$@

#
#
libhcsr04.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared $^ -o $@

#
#
$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

