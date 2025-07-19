#include "list_str.h"

#include <stdbool.h>

ListStr list_Str_new(size_t capacity) {
	ListStr list;

	list.items = (Str *) malloc(capacity * sizeof(Str));
	list.capacity = capacity;
	list.count = 0;
	return list;
}

void list_Str_resize(ListStr *list) {
	Str *new_items;
	size_t i;

	new_items = (Str *) malloc(list->capacity * 2 * sizeof(Str));
	i = 0;
	while (i < list->count) {
		new_items[i] = list->items[i];
		i++;
	}

	free(list->items);
	list->items = new_items;
	list->capacity *= 2;
}

void list_Str_append(ListStr *list, Str value) {
	if (list->count == list->capacity) {
		list_Str_resize(list);
	}
	list->items[list->count++] = value;
}

size_t find(const ListStr *hay, const Str *needle) {
	size_t i;
	size_t j;
	bool found;

	i = 0;
	found = false;
	while (i < hay->count) {
		if (hay->items[i].count == needle->count) {
			j = 0;
			found = true;
			while (j < needle->count) {
				if (needle->items[j] != hay->items[i].items[j]) {
					found = false;
					break;
				}
				j++;
			}
		}
		if (found) {
			return i;
		}
		i++;
	}
	return SIZE_MAX;
}

void list_Str_free(ListStr *list) {
	size_t i;

	i = 0;
	if (list->items != NULL) {
		while (i < list->count) {
			free(list->items[i].items);
			i++;
		}
		free(list->items);
		list->items = NULL;
	}
	list->capacity = 0;
	list->count = 0;
}
