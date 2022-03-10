BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/raspispi.o

MAKE = make
MKDIR = mkdir -p
CC = g++
UTIL_PWD = ../../../util
INTERFACE_PWD = ../../interface
INCLUDE = -Isrc -I$(INTERFACE_PWD)/src -I$(UTIL_PWD)/src
LIBS =

CFLAGS = -g $(INCLUDE) -fPIC
LDFLAGS = $(LIBS)

all: libraspispi.so

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

libraspispi.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@
