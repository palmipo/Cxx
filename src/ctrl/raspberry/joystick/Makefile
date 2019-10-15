OBJECTS = \
	bin/joystick.o

CC = g++
INCLUDE = -I../../.. -Isrc
LIBS = -L. -ljoystick

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

clean:
	rm bin/*.o *.so test_joystick

libjoystick.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

test_joystick: bin/test_joystick.o libjoystick.so
	$(CC) -o $@ $< $(LDFLAGS)

bin/test_joystick.o: test/test_joystick.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
