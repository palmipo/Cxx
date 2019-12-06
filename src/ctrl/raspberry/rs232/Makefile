BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/rs232unix.o \
	$(BIN_PWD)/rs232buffer.o \
	$(BIN_PWD)/rs232fifo.o \
	$(BIN_PWD)/rs232factory.o

MAKE = make
MKDIR = mkdir -p
CC = g++
UTIL_PWD = ../../../util
POLL_PWD = ../poll
LOG_PWD = ../log
INCLUDE = -I$(UTIL_PWD)/src -I$(POLL_PWD)/src -I$(LOG_PWD)/src -Isrc
LIBS = -L. -lutil -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll fwup

rsclb : $(BIN_PWD)/rsclb.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232

$(BIN_PWD)/rsclb.o: test/main.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

fwup : $(BIN_PWD)/fwup.o
	$(MAKE) liblog.so
	$(MAKE) libpoll.so
	$(MAKE) librs232.so
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232

fwup.exe : $(BIN_PWD)/fwup.o
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(MAKE) librs232.dll
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232

$(BIN_PWD)/fwup.o: test/fwup.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

dump.exe : $(BIN_PWD)/dump.o
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(MAKE) librs232.dll
	$(CC) -o $@ $^ $(LDFLAGS) -lrs232 -lpthread

$(BIN_PWD)/dump.o: test/dump.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

# LINUX
libutil.so:
	$(MAKE) -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

librs232.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

# WINDOWS
libutil.dll:
	$(MAKE) -C $(UTIL_PWD) $@
	cp $(UTIL_PWD)/$@ .

liblog.dll:
	$(MAKE) -C $(LOG_PWD) $@
	cp $(LOG_PWD)/$@ .

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
	$(CC) $(CFLAGS) -DMAKE_RS232_DLL -c $^ -o $@
