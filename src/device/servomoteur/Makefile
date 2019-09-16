OBJECTS = \
	bin/sg90.o

I2C_PWD = ../../ctrl/raspberry/i2c
USBI2C_PWD = ../../ctrl/usb_i2c
RS232_PWD = ../../ctrl/raspberry/rs232
CC = g++
MAKE = make
INCLUDE = -I../.. -I../../ctrl/interface -Isrc -I$(RS232_PWD)/src -I$(USBI2C_PWD)/src -I$(I2C_PWD)/src -I../i2c/src
LIBS = -L. -li2cdevice -lservomoteur

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: raspi_servomoteur

clean:
	rm bin/*.o libservomoteur.so libraspii2c.so raspi_servomoteur test_servomoteur

test_servomoteur: bin/test_servomoteur.o libservomoteur.so libi2cdevice.so libusbi2c.so librs232.so
	$(CC) $< -o $@ -lusbi2c -lrs232 $(LDFLAGS)
	
bin/test_servomoteur.o: test/test_servomoteur.cpp
	$(CC) $(CFLAGS) -DUSBI2C -c $^ -o $@

raspi_servomoteur: bin/raspi_servomoteur.o libservomoteur.so libi2cdevice.so libraspii2c.so
	$(CC) $< -o $@ -lraspii2c $(LDFLAGS)
	
bin/raspi_servomoteur.o: test/test_servomoteur.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

librs232.so:
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

libusbi2c.so:
	$(MAKE) -C $(USBI2C_PWD) $@
	ln -s $(USBI2C_PWD)/$@

libraspii2c.so:
	$(MAKE) -C $(I2C_PWD) $@
	ln -s $(I2C_PWD)/$@

libi2cdevice.so:
	$(MAKE) -C ../i2c $@
	ln -s ../i2c/$@

libservomoteur.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

bin/sg90.o: src/sg90.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
