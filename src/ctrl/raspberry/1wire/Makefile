BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/onewire.o \
	$(BIN_PWD)/onewirerom.o

CC = g++
INCLUDE = -I../../interface -I../i2c/src -Isrc
LIBS =

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: libonewire.so

clean:
	rm -f $(BIN_PWD)/*.o libonewire.so libi2c.so

libonewire.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

libi2c.so:
	$(MAKE) -C ../i2c/ $@
	ln -s ../i2c/$@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
