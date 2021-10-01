#ifndef KRILYA_ENCODE_C
#define KRILYA_ENCODE_C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Krilya_Key.c"

int main(int argc, char **argv)
{
	int option;
	char *filename = NULL;
    Krilya_Key_Chain key_chain;

	while((option = getopt(argc, argv, ":f:")) != -1) {
		switch (option) {
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

	if (filename == NULL) {
        printf("A filename (-f) must be given.");
        exit(1);
    }
    
    Krilya_Load_Key_From_File(filename, &key_chain);
    if (key_chain.ready) {
        Krilya_Print_Key_Chain(&key_chain, 1);
    }
    Krilya_Free_Key_Chain(&key_chain);
}

#endif