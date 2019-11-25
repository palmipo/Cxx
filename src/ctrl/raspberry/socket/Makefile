BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/socketbuffer.o \
	$(BIN_PWD)/socketbase.o \
	$(BIN_PWD)/socketcan.o \
	$(BIN_PWD)/sockettcp.o \
	$(BIN_PWD)/sockettcpfifo.o \
	$(BIN_PWD)/socketfactory.o

CC = g++
POLL_PWD = ../poll
INCLUDE = -I$(POLL_PWD)/src -I../log/src -Isrc
LIBS = -L. -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.dll *.so

# LINUX
liblog.so:
	$(MAKE) -C ../log $@
	ln -s ../log/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

libsocket.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

# WINDOWS
liblog.dll:
	$(MAKE) -C ../log $@
	cp ../log/$@ .

libpoll.dll:
	$(MAKE) -C $(POLL_PWD) $@
	cp $(POLL_PWD)/$@ .

libsocket.dll: $(OBJECTS)
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

# GLOBAL
$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -DMAKE_SOCKET_DLL -c $^ -o $@
