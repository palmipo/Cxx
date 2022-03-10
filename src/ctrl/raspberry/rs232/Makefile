BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/rs232unix.o \
	$(BIN_PWD)/rs232factory.o

MAKE = make
MKDIR = mkdir -p
CC = g++

UTIL_PWD = ../../../util
POLL_PWD = ../poll
INCLUDE = -I$(UTIL_PWD)/src -I$(POLL_PWD)/src -Isrc
LIBS = -L. -lpoll

CFLAGS = -g -std=c++11 $(INCLUDE) -DRASPI
LDFLAGS = $(LIBS)

all: librs232.so

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll fwup* dump*

rsclb : $(BIN_PWD)/rsclb.o
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232

$(BIN_PWD)/rsclb.o: test/main.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

fwup : $(BIN_PWD)/fwup.o
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232

fwup.exe : $(BIN_PWD)/fwup.o
	$(MAKE) libpoll.dll
	$(MAKE) librs232.dll
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232

$(BIN_PWD)/fwup.o: test/fwup.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

dump : $(BIN_PWD)/dump.o
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232 -lpthread

dump.exe : $(BIN_PWD)/dump.o
	$(MAKE) libpoll.dll
	$(MAKE) librs232.dll
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232 -lpthread

$(BIN_PWD)/dump.o: test/dump.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

echo : $(BIN_PWD)/echo.o
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232 -lpthread

echo.exe : $(BIN_PWD)/echo.o
	$(MAKE) libpoll.dll
	$(MAKE) librs232.dll
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232 -lpthread

$(BIN_PWD)/echo.o: test/echo.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

# LINUX
libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

librs232.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

# WINDOWS
libpoll.dll:
	$(MAKE) libutil.dll
	$(MAKE) liblog.dll
	$(MAKE) -C $(POLL_PWD) $@
	cp $(POLL_PWD)/$@ .

librs232.dll: $(OBJECTS)
	$(MAKE) libpoll.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

# GLOBAL
$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -fPIC -DMAKE_RS232_DLL -c $^ -o $@
