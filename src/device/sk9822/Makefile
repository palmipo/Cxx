BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/sk9822.o \
	$(BIN_PWD)/sk9822_gpio.o

CC = g++
MAKE = make
INCLUDE = -Isrc
LIBS = -L.

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS) -lpthread

all:

#
#
clean:
	rm -f $(BIN_PWD)/*.o *.so

#
#
main: $(BIN_PWD)/main.o
	$(MAKE) libsk9822.so
	$(CC) -o $@ $^ $(LDFLAGS) -lsk9822

$(BIN_PWD)/main.o: test/main.cpp
	$(CC) $(CFLAGS) -c $^ -o $@


#
#
libsk9822.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared $^ -o $@

#
#
$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

