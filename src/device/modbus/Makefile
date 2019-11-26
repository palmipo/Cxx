BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/modbusbuffer.o \
	$(BIN_PWD)/modbuschannel.o \
	$(BIN_PWD)/modbusfactory.o \
	$(BIN_PWD)/modbusmsg.o \
	$(BIN_PWD)/modbusmsgdirect.o \
	$(BIN_PWD)/modbusmsgfc01.o \
	$(BIN_PWD)/modbusmsgfc02.o \
	$(BIN_PWD)/modbusmsgfc03.o \
	$(BIN_PWD)/modbusmsgfc04.o \
	$(BIN_PWD)/modbusmsgfc05.o \
	$(BIN_PWD)/modbusmsgfc06.o \
	$(BIN_PWD)/modbusmsgfc08.o \
	$(BIN_PWD)/modbusmsgfc11.o \
	$(BIN_PWD)/modbusmsgfc15.o \
	$(BIN_PWD)/modbusmsgfc16.o \
	$(BIN_PWD)/modbusmsgfc23.o \
	$(BIN_PWD)/modbusmsgfc43.o \
	$(BIN_PWD)/modbusmsgfc71.o \
	$(BIN_PWD)/modbusmsgfc72.o \
	$(BIN_PWD)/modbusmsgfc90.o \
	$(BIN_PWD)/modbusmsgheader.o \
	$(BIN_PWD)/modbusqueue.o \
	$(BIN_PWD)/modbusrtu.o \
	$(BIN_PWD)/modbustcp.o

MAKE = make
MKDIR = mkdir -p
CC = g++
RASPI_CTRL = ../../ctrl/raspberry
UTIL_PWD = ../../util
LOG_PWD = $(RASPI_CTRL)/log
POLL_PWD = $(RASPI_CTRL)/poll
SOCKET_PWD = $(RASPI_CTRL)/socket
RS232_PWD = $(RASPI_CTRL)/rs232
INCLUDE = -I$(UTIL_PWD)/src -I$(POLL_PWD)/src -I$(LOG_PWD)/src -Isrc -I$(SOCKET_PWD)/src -I$(RS232_PWD)/src
LIBS = -L. -lutil -llog -lpoll -lrs232 -lsocket

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	$(MAKE) -C $(LOG_PWD) $@
	$(MAKE) -C $(POLL_PWD) $@
	$(MAKE) -C $(RS232_PWD) $@
	$(MAKE) -C $(SOCKET_PWD) $@
	rm -f $(BIN_PWD)/*.o *.so *.dll fwupd modbus_cmd

fwupd: $(BIN_PWD)/fwupd.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(MAKE) libsocket.so
	$(MAKE) libmodbus.so
	$(CC) $^ -o $@ $(LDFLAGS) -lmodbus -lpthread

fwupd.exe: $(BIN_PWD)/fwupd.o
	$(MAKE) libmodbus.dll
	$(CC) $^ -o $@ $(LDFLAGS) -lmodbus -lpthread

$(BIN_PWD)/fwupd.o: test/fwupd.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

modbus_cmd: $(BIN_PWD)/modbus_cmd.o
	$(MAKE) libmodbus.so
	$(CC) $^ -o $@ $(LDFLAGS) -lmodbus -lpthread

$(BIN_PWD)/modbus_cmd.o: test/modbus_cmd.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

#
# LINUX
#
libutil.so:
	$(MAKE) -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

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
libutil.dll:
	$(MAKE) -C $(UTIL_PWD) $@
	cp $(UTIL_PWD)/$@ .

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
	$(MAKE) libutil.dll
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(MAKE) librs232.dll
	$(MAKE) libsocket.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

#
# GLOBAL
#
$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -DMAKE_MODBUS_DLL -c $^ -o $@
