OBJECTS = \
	bin/etherio.o

CC = g++
INCLUDE = -I../interface -I../raspberry/poll/src -I../raspberry/socket/src -Isrc
LIBS = -L. -letherio24 -lsocket
CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: abris_jardin 

clean:
	rm bin/*.o abris_jardin *.so

abris_jardin: bin/abris_jardin.o libetherio24.so libsocket.so
	$(CC) $< -o $@ $(LDFLAGS)

bin/abris_jardin.o: test/abris_jardin.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libetherio24.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

libsocket.so:
	$(MAKE) -C ../raspberry/socket $@
	ln -s ../raspberry/socket/$@

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
