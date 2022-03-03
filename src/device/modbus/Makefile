BIN_PWD = bin/$(HOSTNAME)
ELECTECHSUP_PWD = bin/electechsup/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/modbuschannel.o \
	$(BIN_PWD)/modbusmsg.o \
	$(BIN_PWD)/modbusmsgdirect.o \
	$(BIN_PWD)/modbusmsgfc01.o \
	$(BIN_PWD)/modbusmsgfc02.o \
	$(BIN_PWD)/modbusmsgfc03.o \
	$(BIN_PWD)/modbusmsgfc04.o \
	$(BIN_PWD)/modbusmsgfc05.o \
	$(BIN_PWD)/modbusmsgfc06.o \
	$(BIN_PWD)/modbusmsgfc15.o \
	$(BIN_PWD)/modbusmsgfc16.o \
	$(BIN_PWD)/modbusmsgheader.o \
	$(BIN_PWD)/modbusfifo.o \
	$(BIN_PWD)/modbusrtu.o \
	$(BIN_PWD)/modbustcp.o

ELECTECHSUP = \
	$(ELECTECHSUP_PWD)/r4d3b16.o \
	$(ELECTECHSUP_PWD)/n4dih32.o \
	$(ELECTECHSUP_PWD)/r4dcb08.o

MAKE = make
MKDIR = mkdir -p
CC = g++
RASPI_CTRL = ../../ctrl/raspberry
UTIL_PWD = ../../util
LOG_PWD = $(RASPI_CTRL)/log
POLL_PWD = $(RASPI_CTRL)/poll
SOCKET_PWD = $(RASPI_CTRL)/socket
RS232_PWD = $(RASPI_CTRL)/rs232
INCLUDE = -I$(UTIL_PWD)/src -I$(POLL_PWD)/src -I$(LOG_PWD)/src -Isrc -Ielectechsup/src -I$(SOCKET_PWD)/src -I$(RS232_PWD)/src
LIBS = -L. -lutil -llog -lrs232 -lpoll -lsocket

CFLAGS = -g -std=c++11 $(INCLUDE) -fPIC -DRASPI
LDFLAGS = $(LIBS)

all:

clean:
	$(MAKE) -C $(LOG_PWD) $@
	$(MAKE) -C $(UTIL_PWD) $@
	$(MAKE) -C $(POLL_PWD) $@
	$(MAKE) -C $(RS232_PWD) $@
	$(MAKE) -C $(SOCKET_PWD) $@
	rm -f $(BIN_PWD)/*.o *.so *.dll fwupd modbus_cmd

cabane: $(BIN_PWD)/cabane.o
	$(MAKE) liblog.so
	$(MAKE) libutil.so
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(MAKE) libsocket.so
	$(MAKE) libmodbus.so
	$(MAKE) libelectechsup.so
	$(CC) $^ -o $@ $(LDFLAGS) -lelectechsup -lmodbus -lpthread

$(BIN_PWD)/cabane.o: domotic/cabane.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@

modbus_cmd: $(BIN_PWD)/modbus_cmd.o
	$(MAKE) liblog.so
	$(MAKE) libutil.so
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(MAKE) libsocket.so
	$(MAKE) libmodbus.so
	$(MAKE) libelectechsup.so
	$(CC) $^ -o $@ $(LDFLAGS) -lelectechsup -lmodbus -lpthread

$(BIN_PWD)/modbus_cmd.o: test/modbus_cmd.cpp
	$(MKDIR) $(BIN_PWD)
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

libelectechsup.so: $(ELECTECHSUP)
	$(CC) -shared $^ -o $@

#
# GLOBAL
#
$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -DMAKE_MODBUS_DLL -c $^ -o $@

$(ELECTECHSUP_PWD)/%.o: electechsup/src/%.cpp
	$(MKDIR) $(ELECTECHSUP_PWD)
	$(CC) $(CFLAGS) -DMAKE_MODBUS_DLL -c $^ -o $@
