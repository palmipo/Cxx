BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/raspiuart.o

UTIL_PWD = ../../util
INTERFACE_PWD = ../../ctrl/interface
RASPI_PWD = ../../ctrl/raspberry
POLL_PWD = $(RASPI_PWD)/poll
GPIO_PWD = $(RASPI_PWD)/gpio
RS232_PWD = $(RASPI_PWD)/rs232
CC = g++
MAKE = make
INCLUDE = -Isrc -I$(INTERFACE_PWD)/src -I$(RS232_PWD)/src -I$(POLL_PWD)/src -I$(UTIL_PWD)/src
LIBS = -L.

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

#
#
clean:
	rm -f $(BIN_PWD)/*.o *.so

#
#
libuart.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared $< -o $@

#
#
$(BIN_PWD)/%.o: src/%.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI

