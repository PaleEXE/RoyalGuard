#ifndef LISTSTR_H
#define LISTSTR_H

#include <stdlib.h>
#include "str.h"

typedef struct ListStr {
	Str *items;
	size_t capacity, count;
} ListStr;

ListStr list_Str_new(size_t capacity);

void list_Str_resize(ListStr *list);

void list_Str_append(ListStr *list, Str value);

size_t find(const ListStr *hay, const Str *needle);

void list_Str_free(ListStr *list);

#endif // LISTSTR_H
