BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/parser.o \
	$(BIN_PWD)/dataobjectcollection.o \
	$(BIN_PWD)/dataobjectlist.o \
	$(BIN_PWD)/dataobject.o \
	$(BIN_PWD)/dataobjectitem.o \
	$(BIN_PWD)/exception.o \
	$(BIN_PWD)/grouplist.o \
	$(BIN_PWD)/group.o \
	$(BIN_PWD)/groupitem.o \
	$(BIN_PWD)/choicetypelist.o \
	$(BIN_PWD)/choicetype.o \
	$(BIN_PWD)/choice.o

CC = g++
MAKE = make
MKDIR = mkdir -p
INCLUDE = -Iinclude -I../binaries/include
COPY = cp
#COPY = ln -s
LIBS = -L. -L../binaries/lib ../binaries/lib/libxml2_a.lib ../binaries/lib/iconv_a.lib
CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: altilab.exe

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

altilab.exe: $(BIN_PWD)/altilab.o 
	$(MAKE) libaltilab.dll
	$(CC) $^ -o $@ $(LDFLAGS) -laltilab -L../binaries/lib -lmodbus -ljson -los -static-libgcc -static-libstdc++ -lpthread -lws2_32
	# ../libos/build/targets/libos.a ../libstream/build/targets/libstream.a

$(BIN_PWD)/altilab.o: test/src/altilab.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@ -I../libmodbus/libs/libmodbus/include -I../libos/include -I../libstream/include -DPLATFORM=OS_WIN32

libaltilab.dll: $(OBJECTS)
	$(CC) -shared $^ -o $@ $(LDFLAGS)

$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -DMAKE_ALTILAB_DLL -c $^ -o $@
