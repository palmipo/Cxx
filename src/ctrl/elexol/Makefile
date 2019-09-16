OBJECTS = \
	bin/etherio.o

CC = g++
INCLUDE = -I../interface -I../raspberry/factory/src -I../raspberry/socket/src -Isrc
LIBS = -L. -letherio24 -lsocket
CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: abris_jardin 

clean:
	rm bin/*.o abris_jardin libetherio24.so libsocket.so

abris_jardin: bin/abris_jardin.o libetherio24.so libsocket.so
	$(CC) $< -o $@ $(LDFLAGS)

bin/abris_jardin.o: test/abris_jardin.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libetherio24.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

bin/etherio.o: src/etherio.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libsocket.so:
	$(MAKE) -C ../raspberry/socket $@
	ln -s ../raspberry/socket/$@
