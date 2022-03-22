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
	$(BIN_PWD)/modbusrtu.o \
	$(BIN_PWD)/modbustcp.o

ELECTECHSUP = \
	$(ELECTECHSUP_PWD)/r4d3b16.o \
	$(ELECTECHSUP_PWD)/n4dih32.o \
	$(ELECTECHSUP_PWD)/r4dcb08.o

MAKE = make
MKDIR = mkdir -p
CC = g++
RASPI_PWD = ../../ctrl/raspberry
UTIL_PWD = ../../util
POLL_PWD = $(RASPI_PWD)/poll
RS232_PWD = $(RASPI_PWD)/rs232
SOCKET_PWD = $(RASPI_PWD)/socket
INCLUDE = -Isrc -Ielectechsup/src -I$(RS232_PWD)/src -I$(SOCKET_PWD)/src -I$(UTIL_PWD)/src -I$(POLL_PWD)/src
LIBS = -L.

CFLAGS = -g -std=c++11 $(INCLUDE) -fPIC -DRASPI
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so modbus_cmd

cabane: $(BIN_PWD)/cabane.o libraspi.so libmodbus.so libelectechsup.so
	$(CC) $< -o $@ $(LDFLAGS) -lelectechsup -lmodbus -lraspi

$(BIN_PWD)/cabane.o: domotic/cabane.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@

modbus_cmd: $(BIN_PWD)/modbus_cmd.o libraspi.so libmodbus.so libelectechsup.so
	$(CC) $< -o $@ $(LDFLAGS) -lelectechsup -lmodbus -lraspi

$(BIN_PWD)/modbus_cmd.o: test/modbus_cmd.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@

#
# LINUX
#
libraspi.so:
	$(MAKE) -C $(RASPI_PWD) $@
	ln -s $(RASPI_PWD)/$@

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
