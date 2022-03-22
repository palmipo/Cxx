BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/sim900.o

RASPI_PWD = ../../../ctrl/raspberry
POLL_PWD = $(RASPI_PWD)/poll
RS232_PWD = $(RASPI_PWD)/rs232
UTIL_PWD = ../../../util
I2C_DEVICE_PWD = ../../i2c
HD44780_PWD = ../../hd44780
CC = g++
MAKE = make
INCLUDE = -Isrc -I$(UTIL_PWD)/src -I$(POLL_PWD)/src -I$(RS232_PWD)/src/
LIBS = -L. -lraspi

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: send_sms

clean:
	rm -f $(BIN_PWD)/*.o *.dll *.so send_sms

send_sms: $(BIN_PWD)/send_sms.o libraspi.so libsim900.so
	$(CC) $< -o $@ $(LDFLAGS) -lsim900 -lpthread

$(BIN_PWD)/send_sms.o: test/send_sms.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libsim900.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

libraspi.so:
	$(MAKE) -C $(RASPI_PWD) $@
	ln -s $(RASPI_PWD)/$@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI
