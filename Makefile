default: xdis

xdis:
	mkdir -p build/lib
	cd src && $(MAKE)

clean:
	cd  src && $(MAKE) clean
	rm -rf build
