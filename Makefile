CC=gcc
CFLAGS=`pkg-config --cflags gtk+-2.0` -w
LIBS=`pkg-config --libs gtk+-2.0` -lusb-1.0
INCLUDE=-I/usr/include/libusb-1.0
OBJS= checkapple.o

checkapple: $(OBJS)
	$(CC) $(LIBS) -o checkapple $(OBJS)

checkapple.o: checkapple.c
	$(CC) $(CFLAGS) $(INCLUDE) -c checkapple.c

install:
	/bin/cp checkapple /usr/bin

clean: 
	/bin/rm -f checkapple $(OBJS)
