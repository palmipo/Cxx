BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/raspii2c.o

MAKE = make
MKDIR = mkdir -p
CC = g++
LOG_PWD = ../log
IFACE_PWD = ../../interface
UTIL_PWD = ../../../util
INCLUDE = -I$(UTIL_PWD)/src -I$(IFACE_PWD)/src -Isrc -I$(LOG_PWD)/src
LIBS = -L. -llog

CFLAGS = -g -std=c++11 $(INCLUDE) -fPIC
LDFLAGS = $(LIBS)

all: libraspii2c.so

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

libraspii2c.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@
