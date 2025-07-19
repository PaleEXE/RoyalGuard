#ifndef STR_H
#define STR_H

#include <stdlib.h>

typedef struct Str {
	char *items;
	size_t capacity, count;
} Str;

Str str_new(size_t capacity);

void str_resize(Str *list);

void str_append(Str *list, char value);

Str str_from(const char *input);

void str_print(const Str *str);

#endif // STR_H
