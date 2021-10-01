#ifndef KRILYA_KEY_H
#define KRILYA_KEY_H
#include "Krilya_Type.h"
#include <stdio.h>

/**
 * Function Prototypes
 */
int Krilya_Key_Length_Exponent(unsigned long long length);

Krilya_Key_Chain_Size Krilya_Get_Key_Chain_Size(unsigned long long length);

void Krilya_Init_Key_Chain(Krilya_Key_Chain_Size key_chain_size, Krilya_Key_Chain *key_chain);

void Krilya_Free_Key_Chain(Krilya_Key_Chain *key_chain);

void Krilya_Print_Key_Chain(Krilya_Key_Chain *key_chain, int key_only);

void Krilya_Write_Key_To_File(Krilya_Key_Chain *key_chain, char *filename);

void Krilya_Load_Key_From_File(char *filename, Krilya_Key_Chain *key_chain);

#endif
