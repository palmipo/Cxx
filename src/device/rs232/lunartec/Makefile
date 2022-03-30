BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/lunartec.o

INTERFACE_PWD = ../../../ctrl/interface
RASPI_PWD = ../../../ctrl/raspberry
POLL_PWD = $(RASPI_PWD)/poll
RS232_PWD = $(RASPI_PWD)/rs232
UTIL_PWD = ../../../util
UART_PWD = ..
CC = g++
MAKE = make
INCLUDE = -I$(UTIL_PWD)/src -I$(INTERFACE_PWD)/src -Isrc -I$(POLL_PWD)/src -I$(RS232_PWD)/src -I$(UART_PWD)/src
LIBS = -L. -llunartec -luart -lraspi

CFLAGS = -g $(INCLUDE) -fPIC -DRASPI
LDFLAGS = $(LIBS)

all: lunartec

clean:
	rm $(BIN_PWD)/*.o *.so lunartec

lunartec: $(BIN_PWD)/test_lunartec.o liblunartec.so libuart.so libraspi.so
	$(CC) $< -o $@  $(LDFLAGS)
	
$(BIN_PWD)/test_lunartec.o: test/test_lunartec.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libraspi.so:
	$(MAKE) -C $(RASPI_PWD) $@
	ln -s $(RASPI_PWD)/$@

libuart.so:
	$(MAKE) -C $(UART_PWD) $@
	ln -s $(UART_PWD)/$@

liblunartec.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) -c $^ -o $@
