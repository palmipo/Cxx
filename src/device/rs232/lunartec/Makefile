BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/lunartec.o

RASPI_PWD = ../../../ctrl/raspberry
POLL_PWD = $(RASPI_PWD)/poll
RS232_PWD = $(RASPI_PWD)/rs232
UTIL_PWD = ../../../util
CC = g++
MAKE = make
INCLUDE = -I$(UTIL_PWD)/src -Isrc -I$(POLL_PWD)/src -I$(RS232_PWD)/src
LIBS = -L. -llunartec -lraspi

CFLAGS = -g $(INCLUDE) -fPIC -DRASPI
LDFLAGS = $(LIBS)

all: lunartec

clean:
	rm $(BIN_PWD)/*.o *.so lunartec

lunartec: $(BIN_PWD)/test_lunartec.o liblunartec.so libraspi.so
	$(CC) $< -o $@  $(LDFLAGS)
	
$(BIN_PWD)/test_lunartec.o: test/test_lunartec.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libraspi.so:
	$(MAKE) -C $(RASPI_PWD) $@
	ln -s $(RASPI_PWD)/$@

liblunartec.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) -c $^ -o $@
