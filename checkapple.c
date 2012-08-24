/******************************************
Check Apple
by thenighteagle
email: sega_genesis_console@yahoo.com

A prgram that checks connected USB devices to find one(or more) that has Apple as its vendor.
It prints out the product name if it can find the product's id in the hash table.
********************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>
#include <glib.h>
#define APPLE 0x05ac 

GHashTable* create_apple_list(void){
	int i = 0;
	GHashTable* apple_list = g_hash_table_new(NULL,NULL);
	gint hexes[20]= {0x1290, 0x1292, 0x1294, 0x1297, 0x129c, 0x12a0,
					 0x1291, 0x1293, 0x1299, 0x129e, 0x129a, 0x129f,
					 0x12a2, 0x12a3, 0x12a9, 0x12a4, 0x12a5, 0x12a6,
					 0x129d, 0x12a7};
	gchar *devices[20]= {"iPhone", "iPhone 3G", "iPhone 3GS", 
						 "iPhone 4 GSM", "iPhone 4 CDMA",
						 "iPhone 4S", "iPod touch",
						 "iPod touch 2G", "iPod touch 3G",
						 "iPod touch 4G", "iPad", "iPad 2 Wi-Fi",
						 "iPad 2 GSM", "iPad 2 CDMA", "iPad 2 R2",
						 "iPad 3 Wi-Fi", "iPad 3 CDMA", "iPad 3 Global",
						 "Apple TV 2G", "Apple TV 3g"};

	for(i = 0; i < 20; i++){
		g_hash_table_insert(apple_list, hexes[i], devices[i]);
	}

	return apple_list;
} 

int main (int argc,char **argv){
	libusb_init(NULL);	
	GHashTable* apple_list;
	libusb_device **list;
	struct libusb_device_descriptor desc;
	ssize_t cnt = libusb_get_device_list(NULL, &list);
	ssize_t i = 0;
	gint ret = 0;
	gint found = 0;

	if(cnt < 0){
		printf("There was an error.");
		return 1;
	}

	else{
		apple_list = create_apple_list();
	}

	for(i=0; i < cnt; i++){
		libusb_device *device = list[i];
		ret = libusb_get_device_descriptor(device, &desc);

		if(ret != 0){
		    printf("Unable to get descriptor");
			break;
		}

		if(desc.idVendor == APPLE){
			found = 1;
			gchar* result;
			gint key = desc.idProduct;
			result = g_hash_table_lookup(apple_list, key);
			printf("%s\n", result);
		}
	}

	if(found == 0){
		printf("Unable to find Apple device\n");
	}

	return 0;
}			
