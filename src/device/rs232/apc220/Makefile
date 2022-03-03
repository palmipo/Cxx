BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/apc220.o

RS232_PWD = ../../../ctrl/raspberry/rs232
GPIO_PWD = ../../../ctrl/raspberry/gpio
POLL_PWD = ../../../ctrl/raspberry/poll
LOG_PWD = ../../../ctrl/raspberry/log
UTIL_PWD = ../../../util
PIA_PWD = ../../pia

CC = g++
MAKE = make
INCLUDE = -Isrc -I$(LOG_PWD)/src -I$(PIA_PWD)/src -I$(UTIL_PWD)/src -I$(POLL_PWD)/src -I$(RS232_PWD)/src -I$(GPIO_PWD)/src
LIBS = -L. -lutil -llog -lpoll -lrs232 -lraspigpio -lpia

CFLAGS = -g $(INCLUDE) -fPIC -DRASPI
LDFLAGS = $(LIBS) -lapc220

all: test_apc220

clean:
	rm -f $(BIN_PWD)/*.o *.so test_apc220

test_apc220: $(BIN_PWD)/test_apc220.o libapc220.so librs232.so libraspigpio.so liblog.so libutil.so libpoll.so libpia.so
	$(CC) $< -o $@ $(LDFLAGS)
	
$(BIN_PWD)/test_apc220.o: test/test_apc220.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libpia.so:
	$(MAKE) -C $(PIA_PWD) $@
	ln -s $(PIA_PWD)/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libutil.so:
	$(MAKE) -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

librs232.so:
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

libraspigpio.so:
	$(MAKE) -C $(GPIO_PWD) $@
	ln -s $(GPIO_PWD)/$@

libapc220.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) -c $^ -o $@
