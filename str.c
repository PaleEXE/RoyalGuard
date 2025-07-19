#include <stdio.h>
#include "str.h"

Str str_new(size_t capacity) {
	Str str;

	str.items = (char *) malloc(capacity * sizeof(char));
	str.capacity = capacity;
	str.count = 0;
	return str;
}

void str_resize(Str *str) {
	char *new_items;
	size_t i;

	new_items = (char *) malloc(str->capacity * 2 * sizeof(char));
	i = 0;
	while (i < str->count) {
		new_items[i] = str->items[i];
		i++;
	}

	free(str->items);
	str->items = new_items;
	str->capacity *= 2;
}

void str_append(Str *str, char value) {
	if (str->count == str->capacity) {
		str_resize(str);
	}
	str->items[str->count++] = value;
}

Str str_from(const char *input) {
	Str str;
	size_t i;
	char c;

	str = str_new(8);
	i = 0;
	while ((c = input[i])) {
		str_append(&str, c);
		i++;
	}
	return str;
}

void str_print(const Str *str) {
	size_t i;

	i = 0;
	while (i < str->count) {
		putchar(str->items[i]);
		i++;
	}
}
