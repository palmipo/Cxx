BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/pollfactory.o \
	$(BIN_PWD)/polldevice.o \
	$(BIN_PWD)/pollmutex.o

UTIL_PWD = ../../../util
LOG_PWD = ../log
MAKE = make
MKDIR = mkdir -p
CC = g++
INCLUDE = -Isrc -I$(UTIL_PWD)/src -I$(LOG_PWD)/src
LIBS = -L. -lutil -llog

CFLAGS = -g -std=c++11 $(INCLUDE) -fPIC
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll


test_poll: $(BIN_PWD)/test.o
	$(MAKE) libpoll.so
	$(CC) -o $@ $< $(LDFLAGS) -lpoll

$(BIN_PWD)/test.o: test/test.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

# LINUX
libutil.so:
	$(MAKE) -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libpoll.so: $(OBJECTS) libutil.so liblog.so
	$(CC) -shared $^ -o $@

# GLOBAL
$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@
