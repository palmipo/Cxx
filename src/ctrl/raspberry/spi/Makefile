BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/spi.o \
	$(BIN_PWD)/spiexception.o

MAKE = make
MKDIR = mkdir -p
CC = g++
UTIL_PWD = ../../../util
INCLUDE = -Isrc -I$(UTIL_PWD)/src
LIBS =

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: libspi.so

clean:
	rm $(BIN_PWD)/*.o *.so *.dll

libutil.so:
	$(MAKE) -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

libspi.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@
