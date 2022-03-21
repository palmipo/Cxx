BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/hc1632.o

UTIL_REP = ../../util
RASPI_PWD = ../../ctrl/raspberry
POLL_REP = $(RASPI_PWD)/poll
GPIO_REP = $(RASPI_PWD)/gpio
PIA_REP = ../pia
AR = ar
CC = g++
MAKE = make
INCLUDE = -I$(UTIL_REP)/src -I$(PIA_REP)/src -I$(POLL_REP)/src -I$(GPIO_REP)/src -Isrc
LIBS = -L. -lpia -lraspi -lhc1632 -pthread

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	$(MAKE) -C $(RASPI_PWD) $@
	$(MAKE) -C $(PIA_REP) $@
	rm $(BIN_PWD)/*.o *.so bad test_aff

test_aff: $(BIN_PWD)/test.o libraspi.so libpia.so libhc1632.so
	$(CC) $^ -o $@ $(LDFLAGS)

$(BIN_PWD)/test.o: test/test.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libpia.so:
	$(MAKE) -C $(PIA_REP) $@
	ln -s $(PIA_REP)/$@

libraspi.so:
	$(MAKE) -C $(RASPI_PWD) $@
	ln -s $(RASPI_PWD)/$@

libhc1632.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) -c $^ -o $@
