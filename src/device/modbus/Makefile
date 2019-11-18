OBJECTS = \
	bin/modbusbuffer.o \
	bin/modbuschannel.o \
	bin/modbusfactory.o \
	bin/modbusmsg.o \
	bin/modbusmsgdirect.o \
	bin/modbusmsgfc01.o \
	bin/modbusmsgfc02.o \
	bin/modbusmsgfc03.o \
	bin/modbusmsgfc04.o \
	bin/modbusmsgfc05.o \
	bin/modbusmsgfc06.o \
	bin/modbusmsgfc08.o \
	bin/modbusmsgfc11.o \
	bin/modbusmsgfc15.o \
	bin/modbusmsgfc16.o \
	bin/modbusmsgfc23.o \
	bin/modbusmsgfc43.o \
	bin/modbusmsgfc71.o \
	bin/modbusmsgfc72.o \
	bin/modbusmsgfc90.o \
	bin/modbusmsgheader.o \
	bin/modbusqueue.o \
	bin/modbusrtu.o \
	bin/modbustcp.o
	
RASPI_CTRL = ../ctrl/raspberry
LOG_PWD = $(RASPI_CTRL)/log
POLL_PWD = $(RASPI_CTRL)/poll
SOCKET_PWD = $(RASPI_CTRL)/socket
RS232_PWD = $(RASPI_CTRL)/rs232
CC = g++
MAKE = make
INCLUDE = -I$(POLL_PWD)/src -I$(LOG_PWD)/src -Isrc -I$(SOCKET_PWD)/src -I$(RS232_PWD)/src
LIBS = -L. -llog -lpoll -lrs232 -lsocket

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	$(MAKE) -C $(LOG_PWD) $@
	$(MAKE) -C $(POLL_PWD) $@
	$(MAKE) -C $(RS232_PWD) $@
	$(MAKE) -C $(SOCKET_PWD) $@
	rm -f bin/*.o *.so *.dll fwupd modbus_cmd

fwupd: bin/fwupd.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(MAKE) libsocket.so
	$(MAKE) libmodbus.so
	$(CC) $^ -o $@ $(LDFLAGS) -lmodbus -lpthread

bin/fwupd.o: test/fwupd.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

modbus_cmd: bin/modbus_cmd.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(MAKE) libsocket.so
	$(MAKE) libmodbus.so
	$(CC) $^ -o $@ $(LDFLAGS) -lmodbus -lpthread

bin/modbus_cmd.o: test/modbus_cmd.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
# LINUX
#
liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

librs232.so:
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

libsocket.so:
	$(MAKE) -C $(SOCKET_PWD) $@
	ln -s $(SOCKET_PWD)/$@

libmodbus.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

#
# MINGW
#
liblog.dll:
	$(MAKE) -C $(LOG_PWD) $@
	cp $(LOG_PWD)/$@ .

libpoll.dll:
	$(MAKE) -C $(POLL_PWD) $@
	cp $(POLL_PWD)/$@ .

librs232.dll:
	$(MAKE) -C $(RS232_PWD) $@
	cp $(RS232_PWD)/$@ .

libsocket.dll:
	$(MAKE) -C $(SOCKET_PWD) $@
	cp $(SOCKET_PWD)/$@ .

libmodbus.dll: $(OBJECTS)
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(MAKE) librs232.dll
	$(MAKE) libsocket.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

#
# GLOBAL
#
bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -DMAKE_MODBUS_DLL -c $^ -o $@
