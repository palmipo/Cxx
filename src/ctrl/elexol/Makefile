BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/etherio.o

CC = g++
INCLUDE = -I../raspberry/poll/src -I../raspberry/socket/src -Isrc
LIBS = -L. -letherio24 -lsocket
CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: abris_jardin 

clean:
	rm $(BIN_PWD)/*.o abris_jardin *.so

abris_jardin: $(BIN_PWD)/abris_jardin.o libetherio24.so libsocket.so
	$(CC) $< -o $@ $(LDFLAGS)

$(BIN_PWD)/abris_jardin.o: test/abris_jardin.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libetherio24.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

libsocket.so:
	$(MAKE) -C ../raspberry/socket $@
	ln -s ../raspberry/socket/$@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
