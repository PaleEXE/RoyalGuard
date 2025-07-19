#include "str_util.h"
#include <stdio.h>
#include <stdbool.h>

Str concat(const Str *str0, const Str *str1) {
	Str result;
	size_t i;

	result = str_new(str0->count + str1->count);
	i = 0;
	while (i++ < str0->count) result.items[i] = str0->items[i];
	i = 0;
	while (i++ < str1->count) result.items[str0->count + i] = str1->items[i];
	result.count = result.capacity;
	return result;
}

Str pad_zeros(Str *str) {
	Str result;
	size_t zeros;
	size_t i;

	zeros = (3 - str->count % 3) % 3;
	result = str_new(str->count + zeros);
	i = 0;
	while (i < zeros) {
		result.items[i] = '0';
		i++;
	}
	i = 0;
	while (i < str->count) {
		result.items[zeros + i] = str->items[i];
		i++;
	}
	result.count = result.capacity;
	return result;
}

Str trim(const Str *input) {
	Str result;
	size_t i;
	char ch;
	bool in_word;

	result = str_new(16);
	i = 0;
	in_word = false;
	while (input->items[i] == ' ') {
		i++;
	}

	while (i < input->count && ((ch = input->items[i]))) {
		if (ch == ' ') {
			if (in_word) {
				str_append(&result, ' ');
				in_word = false;
			}
		} else {
			str_append(&result, ch);
			in_word = true;
		}
		i++;
	}
	if (result.count > 0 && result.items[result.count - 1] == ' ') {
		result.count--;
	}
	return result;
}


Str read_file(const char *file_path) {
	FILE *file;
	Str buf;
	char c;

	buf = str_new(128);
	file = fopen(file_path, "r");
	if (file == NULL) return buf;
	while (fread(&c, 1, 1, file)) str_append(&buf, c);
	return buf;
}

ListStr split(const Str *input, char delim) {
	ListStr result;
	Str current;
	char ch;
	size_t i;

	result = list_Str_new(4);
	current = str_new(8);
	i = 0;
	while (i < input->count && ((ch = input->items[i]))) {
		if (ch == delim) {
			if (current.count > 0) {
				list_Str_append(&result, current);
				current = str_new(8);
			}
		} else {
			str_append(&current, ch);
		}
		i++;
	}
	if (current.count > 0) list_Str_append(&result, current);
	else free(current.items);
	return result;
}
