BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/ant.o \
	$(BIN_PWD)/antfactory.o \
	$(BIN_PWD)/antprofile.o \
	$(BIN_PWD)/antprofilecallback.o \
	$(BIN_PWD)/antprofilesend.o \
	$(BIN_PWD)/antslave.o \
	$(BIN_PWD)/anthr.o \
	$(BIN_PWD)/antspeedcadence.o \
	$(BIN_PWD)/anttempe.o

#	$(BIN_PWD)/antmaster.o \
#	$(BIN_PWD)/antctrl.o \

LOG_REP = ../../ctrl/raspberry/log
UTIL_REP = ../../util
POLL_REP = ../../ctrl/raspberry/poll
RS232_REP = ../../ctrl/raspberry/rs232
CC = g++
MAKE = make
MKDIR = mkdir -p
INCLUDE = -Isrc -I$(UTIL_REP)/src -I$(LOG_REP)/src -I$(POLL_REP)/src  -Isrc -I$(RS232_REP)/src
LIBS = -L. -lrs232 -lpoll -llog -lutil

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: test_ant

clean:
	make -C $(LOG_REP) clean
	make -C $(POLL_REP) clean
	make -C $(RS232_REP) clean
	rm -f $(BIN_PWD)/*.o *.so *.dll test_ant*

test_ant: $(BIN_PWD)/test_ant.o
	$(MAKE) libant.so
	$(MAKE) librs232.so
	$(MAKE) libpoll.so
	$(MAKE) liblog.so
	$(MAKE) libutil.so
	$(CC) $< -o $@ $(LDFLAGS) -lant -lpthread

libutil.so:
	$(MAKE) -C $(UTIL_REP) $@
	ln -s $(UTIL_REP)/$@

liblog.so:
	$(MAKE) -C $(LOG_REP) $@
	ln -s $(LOG_REP)/$@

libpoll.so:
	$(MAKE) -C $(POLL_REP) $@
	ln -s $(POLL_REP)/$@

librs232.so:
	$(MAKE) -C $(RS232_REP) $@
	ln -s $(RS232_REP)/$@

libant.so: $(OBJECTS)
	$(CC) -shared $^ -o $@ $(LDFLAGS)

test_ant.exe: $(BIN_PWD)/test_ant.o
	$(MAKE) librs232.dll
	$(MAKE) libpoll.dll
	$(MAKE) liblog.dll
	$(MAKE) libutil.dll
	$(MAKE) libant.dll
	$(CC) $< -o $@ $(LDFLAGS) -lant -lpthread

libutil.dll:
	$(MAKE) -C $(UTIL_REP) $@
	ln -s $(UTIL_REP)/$@

liblog.dll:
	$(MAKE) -C $(LOG_REP) $@
	ln -s $(LOG_REP)/$@

libpoll.dll:
	$(MAKE) -C $(POLL_REP) $@
	ln -s $(POLL_REP)/$@

librs232.dll:
	$(MAKE) -C $(RS232_REP) $@
	ln -s $(RS232_REP)/$@

libant.dll: $(OBJECTS)
	$(CC) -shared $^ -o $@ $(LDFLAGS)

$(BIN_PWD)/test_ant.o: test/test_ant.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@
