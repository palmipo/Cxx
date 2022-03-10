BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/raspigpio.o \
	$(BIN_PWD)/raspigpiofactory.o

MKDIR = mkdir -p
MAKE = make
CC = g++
POLL_PWD = ../poll
UTIL_PWD = ../../../util
INCLUDE = -I$(POLL_PWD)/src -I$(UTIL_PWD)/src -Isrc
LIBS = -L. -lpoll -lutil

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll out

in: $(BIN_PWD)/in.o libraspigpio.so libpoll.so
	$(MAKE) libpoll.so
	$(MAKE) libraspigpio.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspigpio -pthread

$(BIN_PWD)/in.o: test/in.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

out: $(BIN_PWD)/out.o libraspigpio.so libpoll.so
	$(MAKE) libpoll.so
	$(MAKE) libraspigpio.so
	$(CC) -o $@ $< $(LDFLAGS) -lraspigpio

$(BIN_PWD)/out.o: test/out.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

# LINUX
libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

libraspigpio.so: $(OBJECTS) libpoll.so
	$(CC) -shared $^ -o $@

# GLOBAL
$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI
