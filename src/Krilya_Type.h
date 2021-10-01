#ifndef KRILYA_TYPE_H
#define KRILYA_TYPE_H

#define KEY_CHARS_MIN 33
#define KEY_CHARS_MAX 126

typedef struct Krilya_Key_Chain_Size_Struct Krilya_Key_Chain_Size;

typedef struct Krilya_Key_Chain_Struct Krilya_Key_Chain;

struct Krilya_Key_Chain_Size_Struct {
	int rows;
	int columns;
} Krilya_Key_Chain_Size_Struct; 

struct Krilya_Key_Chain_Struct {
	int **rows;
	int ready;
	Krilya_Key_Chain_Size size;
} Krilya_Key_Chain_Struct;

#endif