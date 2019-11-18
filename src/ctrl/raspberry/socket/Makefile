OBJECTS = \
	bin/socketbuffer.o \
	bin/socketbase.o \
	bin/socketcan.o \
	bin/sockettcp.o \
	bin/sockettcpfifo.o \
	bin/socketfactory.o

CC = g++
POLL_PWD = ../poll
INCLUDE = -I$(POLL_PWD)/src -I../log/src -Isrc
LIBS = -L. -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f bin/*.o *.dll *.so

# LINUX
liblog.so:
	$(MAKE) -C ../log $@
	ln -s ../log/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

libsocket.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

# WINDOWS
liblog.dll:
	$(MAKE) -C ../log $@
	cp ../log/$@ .

libpoll.dll:
	$(MAKE) -C $(POLL_PWD) $@
	cp $(POLL_PWD)/$@ .

libsocket.dll: $(OBJECTS)
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

# GLOBAL
bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -DMAKE_SOCKET_DLL -c $^ -o $@
