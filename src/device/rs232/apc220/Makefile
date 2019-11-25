BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/apc220.o

RS232_PWD = ../../../ctrl/raspberry/rs232
GPIO_PWD = ../../../ctrl/raspberry/gpio_irq

CC = g++
MAKE = make
INCLUDE = -I../../../ctrl/raspberry/factory/src -I../../../ctrl/interface -Isrc -I$(RS232_PWD)/src/ -I$(GPIO_PWD)/src/
LIBS = -L. -lapc220 -lrs232 -lgpio

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: test_apc220

clean:
	rm -f $(BIN_PWD)/*.o libapc220.so librs232.so libgpio.so test_apc220

test_apc220: $(BIN_PWD)/test_apc220.o libapc220.so librs232.so libgpio.so
	$(CC) $< -o $@ $(LDFLAGS)
	
$(BIN_PWD)/test_apc220.o: test/test_apc220.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

librs232.so:
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

libgpio.so:
	$(MAKE) -C $(GPIO_PWD) $@
	ln -s $(GPIO_PWD)/$@

libapc220.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
