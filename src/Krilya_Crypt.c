#ifndef KRILYA_CRYPT_C
#define KRILYA_CRYPT_C
#include "Krilya_Key.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

/**
 * Takes a character int value, the current col and row positions and the key chain.
 * Based off of this, it will seek the next value to shuffle and update the 
 * current x and y position.
 * 
 * For instance, if the current col and row positions are both 0, we start at the beginning
 * of the key chain. We then move how many times the value of the current char along
 * the key chain, updating the final col and row position for the next interation. 
 * 
 * Finally, we return the char int value at the current point in the key chain.
 */
int Krilya_Seek_Key_Chain_Char(int ch, int *row, int *col, Krilya_Key_Chain *key_chain) {
    if (!key_chain->ready) return 0;

    int current = (*row * key_chain->size.rows) + *col;
    int shift = current + ch;
    int size = key_chain->size.rows * key_chain->size.columns;

    while (shift > size) {
        shift -= size;
    }

    *row = (int) ceil((float) shift / (float) key_chain->size.rows - 1);
    *col = (int) abs(shift - 1 - (*row * key_chain->size.rows));

    return key_chain->rows[*row][*col];
}

/**
 * Encodes text using an initialized key chain.
 */
int* Krilya_Encode_Text(unsigned char *text, Krilya_Key_Chain *key_chain) {
    // Key chain must be initialized before using.
    if (!key_chain->ready) return NULL;
    // *encoding = (int *) malloc(strlen(text) * sizeof(int));
    int *encoding = malloc(strlen(text) * sizeof(int));
    int shift;
    int shifted_val;
    int col = 0;
    int row = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        shift = Krilya_Seek_Key_Chain_Char(text[i], &row, &col, key_chain);
        shifted_val = (text[i] + shift) * shift;
        encoding[i] = shifted_val;
    }

    return encoding;
}


#endif