OBJECTS = \
	bin/canopenfactory.o \
	bin/canopenbuffer.o \
	bin/canopensdobuffer.o \
	bin/canopenstatemachine.o \
	bin/canopenfifo.o \
	bin/canopennmt.o \
	bin/canopensync.o \
	bin/canopenemcy.o \
	bin/canopenguard.o \
	bin/canopenpdo.o \
	bin/canopensdo.o \
	bin/canopen.o

POLL_PWD = ../factory
SOCKET_PWD = ../socket
CAN_PWD = ../can
CC = g++
INCLUDE = -I../log/src -I$(SOCKET_PWD)/src -I$(CAN_PWD)/src -I$(POLL_PWD)/src -Isrc
LIBS = -L. -lcan -lsocket -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: libcanopen.dll

clean:
	rm -f bin/*.o *.so *.dll

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

libcan.so:
	$(MAKE) -C $(CAN_PWD) $@
	ln -s $(CAN_PWD)/$@

libcanopen.so: $(OBJECTS)
	$(MAKE) libcan.so
	$(MAKE) libsocket.so
	$(MAKE) libpoll.so
	$(MAKE) liblog.so
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

libcan.dll:
	$(MAKE) -C $(CAN_PWD) $@
	cp $(CAN_PWD)/$@ .

libcanopen.dll: $(OBJECTS)
	$(MAKE) libcan.dll
	$(MAKE) libsocket.dll
	$(MAKE) libpoll.dll
	$(MAKE) liblog.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
