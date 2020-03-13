BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/canbus.o \
	$(BIN_PWD)/ctrl.o \
	$(BIN_PWD)/ctrlconfig.o \
	$(BIN_PWD)/ctrlconfigbase.o \
	$(BIN_PWD)/ctrlconfigcanatnet.o \
	$(BIN_PWD)/ctrlconfigip.o \
	$(BIN_PWD)/ctrlconfigserial.o \
	$(BIN_PWD)/element.o \
	$(BIN_PWD)/drive.o \
	$(BIN_PWD)/exception.o \
	$(BIN_PWD)/factory.o \
	$(BIN_PWD)/interface.o \
	$(BIN_PWD)/modbus.o \
	$(BIN_PWD)/plc.o \
	$(BIN_PWD)/signal.o \
	$(BIN_PWD)/index.o \
	$(BIN_PWD)/command.o \
	$(BIN_PWD)/cmdmodbus.o \
	$(BIN_PWD)/power.o

CC = g++
MAKE = make
MKDIR = mkdir -p

RASPI_CTRL = ../../ctrl/raspberry
UTIL_PWD = ..
LOG_PWD = $(RASPI_CTRL)/log
POLL_PWD = $(RASPI_CTRL)/poll
SOCKET_PWD = $(RASPI_CTRL)/socket
RS232_PWD = $(RASPI_CTRL)/rs232
DEVICE_PWD = ../../device
MODBUS_PWD = $(DEVICE_PWD)/modbus

INCLUDE = -Iinclude -Ilibxml2/include -I$(LOG_PWD)/src
COPY = cp
LIBS = -L. -Llibxml2/lib -lxml2 -llog
CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: bic.exe

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

bic.exe: $(BIN_PWD)/bic.o 
	$(MAKE) libbic.dll
	$(CC) $^ -o $@ $(LDFLAGS) -lbic -lpthread -lmodbus -lsocket -lpoll -llog

$(BIN_PWD)/bic.o: test/src/bic.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(UTIL_PWD)/src -I$(LOG_PWD)/src -I$(POLL_PWD)/src -I$(SOCKET_PWD)/src -I$(RS232_PWD)/src -I$(MODBUS_PWD)/src

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

libmodbus.dll:
	$(MAKE) -C $(MODBUS_PWD) $@
	cp $(MODBUS_PWD)/$@ .

libbic.dll: $(OBJECTS)
	$(MAKE) libutil.dll
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(MAKE) librs232.dll
	$(MAKE) libsocket.dll
	$(MAKE) libmodbus.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -DMAKE_BIC_DLL -c $^ -o $@
