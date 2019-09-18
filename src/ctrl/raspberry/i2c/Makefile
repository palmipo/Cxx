OBJECTS = \
	bin/raspii2c.o

CC = g++
INCLUDE = -I../../interface -Isrc -I../log/src
LIBS = -L. -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: libraspii2c.so

clean:
	rm -f bin/*.o libraspii2c.so

libraspii2c.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
