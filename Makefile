MAKE = make

all: lib

clean:
	$(MAKE) -C module clean
	$(MAKE) -C tests clean
	$(MAKE) -C src clean

lib:
	$(MAKE) -C src all
