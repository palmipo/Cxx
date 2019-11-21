OBJECTS = \
	bin/log.o

CC = g++
INCLUDE = -Isrc
LIBS =

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f bin/*.o *.so *.dll

liblog.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

liblog.dll: $(OBJECTS)
	$(CC) -shared $^ -o $@

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -DMAKE_LOG_DLL -c $^ -o $@
