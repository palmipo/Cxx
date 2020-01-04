OBJECTS = \
	bin/sim900buffer.o \
	bin/sim900.o

POLL_PWD = ../../../ctrl/raspberry/poll
LOG_PWD = ../../../ctrl/raspberry/log
RS232_PWD = ../../../ctrl/raspberry/rs232
CC = g++
MAKE = make
INCLUDE = -I$(POLL_PWD)/src -I$(LOG_PWD)/src -Isrc -I$(RS232_PWD)/src/ -I$(I2C_PWD)/src/ -I$(I2C_DEVICE_PWD)/src/ -I$(HD44780_PWD)/src/
LIBS = -L. -lrs232 -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: send_sms

clean:
	$(MAKE) -C $(LOG_PWD) $@
	$(MAKE) -C $(POLL_PWD) $@
	$(MAKE) -C $(RS232_PWD) $@
	rm -f bin/*.o *.dll *.so send_sms

send_sms: bin/send_sms.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE)	librs232.so
	$(MAKE) libsim900.so
	$(CC) $< -o $@ $(LDFLAGS) -lsim900 -lpthread

send_sms.exe: bin/send_sms.o
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(MAKE)	librs232.dll
	$(MAKE) libsim900.dll
	$(CC) $< -o $@ $(LDFLAGS) -lsim900 -lpthread

bin/send_sms.o: test/send_sms.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libsim900.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

librs232.so:
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

libsim900.dll: $(OBJECTS)
	$(CC) -shared $^ -o $@

libpoll.dll:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

liblog.dll:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

librs232.dll:
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
