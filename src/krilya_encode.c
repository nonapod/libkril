#ifndef KRILYA_ENCODE_C
#define KRILYA_ENCODE_C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Krilya_Key.c"
#include "Krilya_Crypt.c"
#include <locale.h>

int main(int argc, char **argv)
{
	setlocale(LC_ALL,"UTF-8");
	int option = 0;
	int help = 0;
	int print_encoding = 0;
	char *key = NULL;
	char *filename = NULL;
	unsigned char *text = NULL;
	int *encoding = NULL;
    Krilya_Key_Chain key_chain;

	while((option = getopt(argc, argv, ":k:t:f:hp")) != -1) {
		switch (option) {
			case 'k':
				key = optarg;
				break;
			case 't':
				text = optarg;
				break;
			case 'f':
				filename = optarg;
				break;
			case 'h':
				help = 1;
				break;
			case 'p':
				print_encoding = 1;
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

	if (help || argc == 1) {
		printf("Encodes a string or file using a previously generated key, options are:\n");
		printf("-k a key filename with path. \n");
		printf("-f a file to encode. \n");
		printf("-t a string of text to encode, will be ignored if a file is provided. \n");
		printf("-p prints the encoding to the terminal in hexidecimal format. \n");
		printf("-h display these options. \n");
		exit(0);
	}

	if (key == NULL) {
        printf("A key filename (-k) must be given.");
        exit(1);
    }
	if (text == NULL && filename == NULL) {
		printf("Either a filename (-f) or text (-t) must be provided for encoding.");
		exit(1);
	}
    
    Krilya_Load_Key_From_File(key, &key_chain);
    if (key_chain.ready) {
		encoding = Krilya_Encode_Text(text, &key_chain);
		if (encoding != NULL) {
			FILE *filep;
			if ((filep = fopen("test_encode.txt", "wb+")) != NULL) {
				for (int i = 0; encoding[i] != '\0'; i++) {
					fprintf(filep, "%c", encoding[i]);
					if (print_encoding) printf("0x%x", (unsigned char) encoding[i]);
				} 
				fclose(filep);
			}
			free(encoding);
		}
		Krilya_Free_Key_Chain(&key_chain);
    }
	else {
		printf("Unable to load keychain from: %s\n", key);
	}
}

#endif