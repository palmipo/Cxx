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
POLL_REP = ../../ctrl/raspberry/poll
RS232_REP = ../../ctrl/raspberry/rs232
CC = g++
MAKE = make
INCLUDE = -I../../ctrl/interface -I$(LOG_REP)/src -I$(POLL_REP)/src  -Isrc -I$(RS232_REP)/src
LIBS = -L. -lant -lrs232 -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: libant.so test_ant

clean:
	make -C $(LOG_REP) clean
	make -C $(POLL_REP) clean
	make -C $(RS232_REP) clean
	rm -f $(BIN_PWD)/*.o libant.so librs232.so test_ant

test_ant: $(BIN_PWD)/test_ant.o libant.so librs232.so libpoll.so liblog.so
	$(CC) $< -o $@ $(LDFLAGS)

$(BIN_PWD)/test_ant.o: test/test_ant.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

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
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
