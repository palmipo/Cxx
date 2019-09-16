OBJECTS = \
	bin/towerdevice.o \
	bin/genericdevice.o \
	bin/pollfactory.o \
	bin/polldevice.o \
	bin/pollmutex.o \
	bin/pollbuffer.o

MAKE = make
CC = g++
INCLUDE = -Isrc -I../log/src
LIBS = -L. -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f bin/*.o *.so *.dll

# LINUX
liblog.so:
	$(MAKE) -C ../log $@
	ln -s ../log/$@

libpoll.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

# WINDOWS
liblog.dll:
	$(MAKE) -C ../log $@
	cp ../log/$@ .

libpoll.dll: $(OBJECTS)
	$(MAKE) liblog.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

# GLOBAL
bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -DMAKE_POLL_FACTORY_DLL -c $^ -o $@
