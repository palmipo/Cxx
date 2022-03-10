BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/fifo.o

LOG_PWD = ../../src/ctrl/raspberry/log
MAKE = make
MKDIR = mkdir -p
CC = g++
INCLUDE = -Isrc
LIBS = -L.

CFLAGS = -g -std=c++11 $(INCLUDE) -fPIC
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll test_callback test_callback.exe

test_callback: $(BIN_PWD)/test_callback.o
	$(MAKE) liblog.so
	$(CC) -o $@ $^ $(LIBS) -llog

test_callback.exe: $(BIN_PWD)/test_callback.o
	$(MAKE) liblog.dll
	$(CC) -o $@ $^ $(LIBS) -llog

$(BIN_PWD)/test_callback.o: test/test_callback.cpp
	$(CC) $(CFLAGS) -I$(LOG_PWD)/src -c $^ -o $@

# LINUX
liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

# WINDOWS
liblog.dll:
	$(MAKE) -C $(LOG_PWD) $@
	cp $(LOG_PWD)/$@ .
