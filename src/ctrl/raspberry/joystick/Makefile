BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/joystick.o \
	$(BIN_PWD)/forcefeedback.o

CC = g++
MAKE = make
MKDIR = mkdir -p
UTIL_PWD = ../../../util
LOG_PWD = ../log
POLL_PWD = ../poll
INCLUDE = -I$(LOG_PWD)/src -I$(UTIL_PWD)/src -I$(POLL_PWD)/src -Isrc
LIBS = -L. -ljoystick -lutil -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE) -fPIC
LDFLAGS = $(LIBS)

all: libjoystick.so
	$(MAKE) libjoystick.so

clean:
	rm -f $(BIN_PWD)/*.o *.so test_joystick

test_joystick: $(BIN_PWD)/test_joystick.o
	$(MAKE) libutil.so
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) libjoystick.so
	$(CC) -o $@ $< $(LDFLAGS)

$(BIN_PWD)/test_joystick.o: test/test_joystick.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libutil.so:
	$(MAKE) -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

libjoystick.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@
