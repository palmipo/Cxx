MAKE = make

all: raspberry

clean:
	$(MAKE) -C raspberry clean
	$(MAKE) -C usb_i2c clean
	$(MAKE) -C usb_rs485 clean

raspberry: 
	$(MAKE) -C raspberry all
	$(MAKE) -C usb_i2c all
	$(MAKE) -C usb_rs485 all
