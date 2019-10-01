OBJECTS = \
	bin/rs232unix.o \
	bin/rs232buffer.o \
	bin/rs232fifo.o \
	bin/rs232factory.o

MAKE = make
CC = g++
POLL_PWD = ../factory
INCLUDE = -I$(POLL_PWD)/src -I../log/src -Isrc
LIBS = -L. -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f bin/*.o *.so *.dll

fwup : bin/fwup.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232

fwup.exe : bin/fwup.o
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(MAKE) librs232.dll
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232

bin/fwup.o: test/fwup.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

# LINUX
liblog.so:
	$(MAKE) -C ../log $@
	ln -s ../log/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

librs232.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

# WINDOWS
liblog.dll:
	$(MAKE) -C ../log $@
	cp ../log/$@ .

libpoll.dll:
	$(MAKE) -C $(POLL_PWD) $@
	cp $(POLL_PWD)/$@ .

librs232.dll: $(OBJECTS)
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

# GLOBAL
bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -DMAKE_RS232_DLL -c $^ -o $@
