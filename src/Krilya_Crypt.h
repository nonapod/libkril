#ifndef KRILYA_CRYPT_H
#define KRILYA_CRYPT_H
#include "Krilya_Key.h"

int* Krilya_Encode_Text(unsigned char *text, Krilya_Key_Chain *key_chain);

int Krilya_Seek_Key_Chain_Char(int ch, int *row, int *col, Krilya_Key_Chain *key_chain);


#endif