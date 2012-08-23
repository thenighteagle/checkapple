checkapple
==========

A program that uses libusb to tell the user which apple product they have.

I guess you want to compile this crap.. on Linux I compiled it with:

gcc checkapple.c -o checkapple -I/usr/include/libusb-1.0 `pkg-config –cflags –libs gtk+-2.0` -lusb-1.0

If you have any apple device in the list above then plug it into your computer and run the program. 
It should list out the name of your device.