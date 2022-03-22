BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/apc220.o

RASPI_PWD = ../../../ctrl/raspberry
RS232_PWD = $(RASPI_PWD)/rs232
GPIO_PWD = $(RASPI_PWD)/gpio
POLL_PWD = $(RASPI_PWD)/poll
UTIL_PWD = ../../../util
PIA_PWD = ../../pia

CC = g++
MAKE = make
INCLUDE = -Isrc -I$(PIA_PWD)/src -I$(UTIL_PWD)/src -I$(POLL_PWD)/src -I$(RS232_PWD)/src -I$(GPIO_PWD)/src
LIBS = -L. -lutil -lraspi -lpia

CFLAGS = -g $(INCLUDE) -fPIC -DRASPI
LDFLAGS = $(LIBS) -lapc220

all: test_apc220

clean:
	rm -f $(BIN_PWD)/*.o *.so test_apc220

test_apc220: $(BIN_PWD)/test_apc220.o libapc220.so libraspi.so libpia.so
	$(CC) $< -o $@ $(LDFLAGS)
	
$(BIN_PWD)/test_apc220.o: test/test_apc220.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libpia.so:
	$(MAKE) -C $(PIA_PWD) $@
	ln -s $(PIA_PWD)/$@

libraspi.so:
	$(MAKE) -C $(RASPI_PWD) $@
	ln -s $(RASPI_PWD)/$@

libapc220.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) -c $^ -o $@
