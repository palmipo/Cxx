BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/canbuffer.o \
	$(BIN_PWD)/canbus.o \
	$(BIN_PWD)/ixxatfactory.o \
	$(BIN_PWD)/ixxatusbcan.o \
	$(BIN_PWD)/ixxatcanatnet.o
	
OBJECTS_LINUX = \
	$(OBJECTS) \
	$(BIN_PWD)/ixxatusbcan.o

POLL_PWD = ../poll
SOCKET_PWD = ../socket
CANOPEN_PWD = ../canopen
CC = g++
INCLUDE = -I../log/src -I$(SOCKET_PWD)/src -I$(POLL_PWD)/src -Isrc
LIBS = -L. -llog -lpoll -lsocket

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: libcan.dll

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

	
# LINUX
liblog.so:
	$(MAKE) -C ../log $@
	ln -s ../log/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

libsocket.so:
	$(MAKE) -C $(SOCKET_PWD) $@
	ln -s $(SOCKET_PWD)/$@

libcan.so: $(OBJECTS)
	$(MAKE) libpoll.so
	$(MAKE) libsocket.so
	$(CC) -shared $^ -o $@

# WINDOWS
liblog.dll:
	$(MAKE) -C ../log $@
	cp ../log/$@ .

libpoll.dll:
	$(MAKE) -C $(POLL_PWD) $@
	cp $(POLL_PWD)/$@ .

libsocket.dll:
	$(MAKE) -C $(SOCKET_PWD) $@
	cp $(SOCKET_PWD)/$@ .

libcan.dll: $(OBJECTS)
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(MAKE) libsocket.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
