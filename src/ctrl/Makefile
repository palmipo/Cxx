MAKE = make

all: raspberry

clean:
	$(MAKE) -C raspberry clean
	$(MAKE) -C usb_i2c clean

raspberry: 
	$(MAKE) -C raspberry all
	$(MAKE) -C usb_i2c all
