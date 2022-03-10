BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/pollfactory.o \
	$(BIN_PWD)/polldevice.o

UTIL_PWD = ../../../util
MAKE = make
MKDIR = mkdir -p
CC = g++
INCLUDE = -Isrc -I$(UTIL_PWD)/src
LIBS = -L.

CFLAGS = -g -std=c++11 $(INCLUDE) 
LDFLAGS = $(LIBS)

all: libpoll.so

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll


test_poll: $(BIN_PWD)/test.o libpoll.so
	$(CC) -o $@ $< $(LDFLAGS) -lpoll

$(BIN_PWD)/test.o: test/test.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

# LINUX
libpoll.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

# GLOBAL
$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC
