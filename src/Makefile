CC=gcc
APP=../build/xdisasmbin
CFLAGS= -Wall 
LDFLAGS= -lopcodes -Llibxdisasm/build/lib/ -lxdisasm -lbfd -liberty -lz -ldl


default: all

all: makelib xdisasm

makelib:
	cd libxdisasm && $(MAKE)
	cp libxdisasm/build/lib/libxdisasm.so ../build/lib/libxdisasm.so

xdisasm: main.o
	$(CC) $(CFLAGS) main.o -o ${APP} $(LDFLAGS)

clean:
	rm -rf *.o ${APP}
	rm -rf libxdisasm
