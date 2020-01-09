BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/onewire.o \
	$(BIN_PWD)/onewirerom.o

MAKE = make
MKDIR = mkdir -p
CC = g++
LOG_PWD = ../src/ctrl/raspberry/log
IFACE_PWD = ../../interface
I2C_PWD = ../i2c
INCLUDE = -I$(IFACE_PWD) -I$(I2C_PWD)/src -Isrc
LIBS = -L. -li2c

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

libonewire.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

libi2c.so:
	$(MAKE) -C $(I2C_PWD) $@
	ln -s $(I2C_PWD)/$@

liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@
