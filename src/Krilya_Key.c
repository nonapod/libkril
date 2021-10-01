#ifndef KRILYA_KEY_C
#define KRILYA_KEY_C
#include <stdio.h>
#include <stdlib.h>
// @todo this is linux specific, check this article for more implementations:
// https://paragonie.com/blog/2016/05/how-generate-secure-random-numbers-in-various-programming-languages
#include <sys/random.h>
#include "Krilya_Type.h"

/**
 * Gets the exponent of a power of 2 number thats is
 * greater than 64 i.e 512 -> 9.
 */
int Krilya_Key_Length_Exponent(unsigned long long length) {
	if (length >= 64 && ((length & (length - 1)) == 0)) {
		int pow = 0;
		unsigned long long pos = length;
		while (pos > 1) {
			pos = pos / 2;
			pow++;
		}
		return pow;
	}
	return 0;
}

/**
 * Gets the total columns and rows for a key chain.
 */
Krilya_Key_Chain_Size Krilya_Get_Key_Chain_Size(unsigned long long length) {
	int exponent; 
	int rows;
	int counter;
	int columns;
	Krilya_Key_Chain_Size key_chain_size;

	key_chain_size.rows = 0;
	key_chain_size.columns = 0;

	exponent = Krilya_Key_Length_Exponent(length);
	if (exponent) {
		// Get the total number of rows and columns.
		counter = (int) exponent / 2;	
		rows = 1;
		while (counter) {
			rows = rows * 2;
			counter--;
		}
		columns = (int) length / rows;	
		key_chain_size.rows = rows;
		key_chain_size.columns = columns;
	}

	return key_chain_size;
}

/**
 * Initializes and returns a new key chain.
 * 
 * @todo this function uses getrandom() a linux specific function, create alternative versions.
 *       https://www.delftstack.com/howto/c/c-generate-random-number/
 */
void Krilya_Init_Key_Chain(Krilya_Key_Chain_Size key_chain_size, Krilya_Key_Chain *key_chain) {
	unsigned int rnd;

	// Add the key chain size for reference, then initialize the columns and rows.
	key_chain->size = key_chain_size;
	key_chain->rows = (int**) malloc(key_chain_size.rows * sizeof(int*));
	for (int row = 0; row < key_chain_size.rows; row++) {
		key_chain->rows[row] = (int*) malloc(key_chain_size.columns * sizeof(int));
		for (int column = 0; column < key_chain_size.columns; column++) {
			getrandom(&rnd, sizeof(unsigned int), GRND_NONBLOCK);
			key_chain->rows[row][column] = (rnd % (KEY_CHARS_MAX + 1 - KEY_CHARS_MIN)) + KEY_CHARS_MIN;
		}
	}
	key_chain->ready = 1;
}

/**
 * Frees an existing key chain from memory.
 */
void Krilya_Free_Key_Chain(Krilya_Key_Chain *key_chain) 
{
	for (int row = 0; row < key_chain->size.rows; row++) {
		free(key_chain->rows[row]);
	}
	free(key_chain->rows);
}

/**
 * Prints the key chain to the console.
 */ 
void Krilya_Print_Key_Chain(Krilya_Key_Chain *key_chain, int key_only) {
	for (int row = 0; row < key_chain->size.rows; row++) {
		for (int column = 0; column < key_chain->size.columns; column++) {
			printf("%c", key_chain->rows[row][column]);
		}
		if (!key_only) {
			printf("\n");
		}
	}
}

void Krilya_Write_Key_To_File(Krilya_Key_Chain *key_chain, char *filename) {
	FILE *filep;
	int ch;

	filep = fopen(filename, "wb+");
	for (int row = 0; row < key_chain->size.rows; row++) {
		for (int column = 0; column < key_chain->size.columns; column++) {
			ch = key_chain->rows[row][column];
			fputc(ch, filep);
		}
	}
	fclose(filep);
}

/**
 * Loads a file by filename and initializes key chain if it is of the correct
 * size (power of 2) and contains characters within the max and min char range.
 */
void Krilya_Load_Key_From_File(char *filename, Krilya_Key_Chain *key_chain) {
	int size;
	int ch;
	Krilya_Key_Chain_Size key_chain_size;
	FILE *filep = fopen(filename, "rb");

	if (filep != NULL) {
		// Get the filesize and build a key chain size.
		fseek(filep, 0, SEEK_END);
		size = ftell(filep);
		fseek(filep, 0, SEEK_SET);

		// Build a key chain size struct from the filesize.
		key_chain_size = Krilya_Get_Key_Chain_Size(size);
		if (!key_chain_size.columns || !key_chain_size.rows) return;

		// Now loop all of the chars in the file and make sure they are within the
		// bounds of max and min chars allowed.
		while((ch = fgetc(filep)) != EOF) {
			if (ch < KEY_CHARS_MIN || ch > KEY_CHARS_MAX) return;
		};
		fseek(filep, 0, SEEK_SET);

		// Initialize the keychain, then populate with characters.
		Krilya_Init_Key_Chain(key_chain_size, key_chain);
		if (!key_chain->ready) return;

		for (int row = 0; row < key_chain->size.rows; row++) {
			for (int column = 0; column < key_chain->size.columns; column++) {
				key_chain->rows[row][column] = fgetc(filep);
			}
		}

		fclose(filep);
	}
}

#endif