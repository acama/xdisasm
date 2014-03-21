default: xdisasm

xdisasm:
	cd src && $(MAKE)

clean:
	rm -rf *.o ${APP}
	cd libxdisasm && $(MAKE) clean
