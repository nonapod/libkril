#ifndef KRILYA_MAKE_KEY_C
#define KRILYA_MAKE_KEY_C
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "Krilya_Key.c"

int main(int argc, char **argv)
{
	int option;
	int length = 0;
	char *filename = NULL;
	Krilya_Key_Chain key_chain;

	while((option = getopt(argc, argv, ":l:f:")) != -1) {
		switch (option) {
			case 'l':
				length = atoi(optarg);
				break;
			case 'f':
				filename = optarg;
				break;
			case ':':
				printf("option needs a value\n");
				break;
			case '?': //used for some unknown options
				printf("unknown option: %c\n", option);
				exit(1);
				break;
		}
	}

	if (length < 64 || ((length & (length - 1)) != 0)) {
		printf("Length argument (-l) must be 64 or greater and a power of 2.\n");
		exit(1);
	}

	// Set the key chain size, initialize the key chain and then free it.
	Krilya_Key_Chain_Size key_chain_size = Krilya_Get_Key_Chain_Size(length);
	Krilya_Init_Key_Chain(key_chain_size, &key_chain);

	Krilya_Print_Key_Chain(&key_chain, 1);
	if (filename != NULL) {
		Krilya_Write_Key_To_File(&key_chain, filename);
	}
	Krilya_Free_Key_Chain(&key_chain);
}

#endif