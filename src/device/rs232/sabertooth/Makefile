OBJECTS = \
	bin/sabertooth.o \
	bin/moteurcc.o

RS232_PWD = ../../../ctrl/raspberry/rs232
JOYSTICK_PWD = ../../../ctrl/raspberry/joystick
CC = g++
MAKE = make
INCLUDE = -I../../.. -Isrc -I$(RS232_PWD)/src/ -I$(JOYSTICK_PWD)/src/
LIBS = -L. -lsabertooth -lrs232 -ljoystick

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: libsabertooth.so librs232.so
	echo "library libsabertooth.so"

clean:
	rm bin/*.o libsabertooth.so librs232.so libjoystick.so test_sabertooth

librs232.so:
	$(MAKE) -C $(RS232_PWD)
	ln -s $(RS232_PWD)/librs232.so

libjoystick.so:
	$(MAKE) -C $(JOYSTICK_PWD)
	ln -s $(JOYSTICK_PWD)/libjoystick.so

libsabertooth.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

bin/sabertooth.o: src/sabertooth.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

bin/moteurcc.o: src/moteurcc.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

test_sabertooth: bin/test_sabertooth.o libsabertooth.so librs232.so libjoystick.so
	$(CC) $^ -o $@ $(LDFLAGS)

bin/test_sabertooth.o: test/test_sabertooth.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
