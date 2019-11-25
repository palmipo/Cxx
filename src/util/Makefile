BIN_PWD = bin/$(HOSTNAME)

LOG_PWD = ../src/ctrl/raspberry/log
MAKE = make
CC = g++
INCLUDE = -Isrc -I$(LOG_PWD)/src
LIBS = -L. -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

test_callback: $(BIN_PWD)/test_callback.o
	$(MAKE) liblog.so
	$(CC) -o $@ $^ $(LIBS)

test_callback.exe: $(BIN_PWD)/test_callback.o
	$(MAKE) liblog.dll
	$(CC) -o $@ $^ $(LIBS)

$(BIN_PWD)/test_callback.o: test/test_callback.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

# LINUX
liblog.so:
	$(MAKE) -C ../log $@
	ln -s ../log/$@

# WINDOWS
liblog.dll:
	$(MAKE) -C ../log $@
	cp ../log/$@ .
