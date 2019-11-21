OBJECTS = \
	bin/pollfactory.o \
	bin/polldevice.o \
	bin/pollmutex.o \
	bin/pollbuffer.o

LOG_PWD = ../log
MAKE = make
CC = g++
INCLUDE = -Isrc -I$(LOG_PWD)/src
LIBS = -L. -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f bin/*.o *.so *.dll

# LINUX
liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libpoll.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

# WINDOWS
liblog.dll:
	$(MAKE) -C $(LOG_PWD) $@
	cp $(LOG_PWD)/$@ .

libpoll.dll: $(OBJECTS)
	$(MAKE) liblog.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

# GLOBAL
bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -DMAKE_POLL_FACTORY_DLL -c $^ -o $@
