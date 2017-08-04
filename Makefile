CC=gcc
CFLAGS = -g 
# uncomment this for SunOS
# LIBS = -lsocket -lnsl

all: udp-send udp-server

udp-send: udp-send.o 
	$(CC) -o udp-send udp-send.o $(LIBS)

udp-server: udp-server.o 
	$(CC) -o udp-server udp-server.o $(LIBS)


clean:
	rm -f udp-send udp-server udp-send.o udp-server.o 

	

