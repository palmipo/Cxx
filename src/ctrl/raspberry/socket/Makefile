BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/socketbase.o \
	$(BIN_PWD)/socketcan.o \
	$(BIN_PWD)/sockettcp.o \
	$(BIN_PWD)/socketudp.o \
	$(BIN_PWD)/socketfactory.o

MAKE = make
MKDIR = mkdir -p
CC = g++
UTIL_PWD = ../../../util
POLL_PWD = ../poll
INCLUDE = -I$(UTIL_PWD)/src -I$(POLL_PWD)/src -Isrc
LIBS = -L. -lpoll

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: libsocket.so

clean:
	rm -f $(BIN_PWD)/*.o *.dll *.so

modbus_cmd: $(BIN_PWD)/modbus_cmd.o
	$(MAKE) libpoll.so
	$(MAKE) libsocket.so
	$(CC) $^ -o $@ $(LDFLAGS) -lsocket

$(BIN_PWD)/modbus_cmd.o: test/modbus_cmd.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@

# LINUX
libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

libsocket.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

# WINDOWS
libpoll.dll:
	$(MAKE) -C $(POLL_PWD) $@
	cp $(POLL_PWD)/$@ .

libsocket.dll: $(OBJECTS)
	$(MAKE) libpoll.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

# GLOBAL
$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -DMAKE_SOCKET_DLL -c $^ -o $@ -fPIC
