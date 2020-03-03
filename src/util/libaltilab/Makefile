BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/parser.o \
	$(BIN_PWD)/dataobjectcollection.o \
	$(BIN_PWD)/dataobjectlist.o \
	$(BIN_PWD)/dataobject.o \
	$(BIN_PWD)/dataobjectitem.o \
	$(BIN_PWD)/exception.o \
	$(BIN_PWD)/grouplist.o \
	$(BIN_PWD)/group.o \
	$(BIN_PWD)/groupitem.o \
	$(BIN_PWD)/choicetypelist.o \
	$(BIN_PWD)/choicetype.o \
	$(BIN_PWD)/choice.o

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

INCLUDE = -Iinclude -I/usr/include/libxml2 -I$(LOG_PWD)/src
COPY = cp
LIBS = -L. -lxml2 -llog
CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: altilab.exe

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

altilab.exe: $(BIN_PWD)/altilab.o 
	$(MAKE) libaltilab.dll
	$(CC) $^ -o $@ $(LDFLAGS) -laltilab -lpthread -lmodbus -lsocket -lpoll -llog

$(BIN_PWD)/altilab.o: test/src/altilab.cpp
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

libaltilab.dll: $(OBJECTS)
	$(MAKE) libutil.dll
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(MAKE) librs232.dll
	$(MAKE) libsocket.dll
	$(MAKE) libmodbus.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -DMAKE_ALTILAB_DLL -c $^ -o $@
