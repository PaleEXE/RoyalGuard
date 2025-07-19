#include "more_str_util.h"

bool str_eq_cstr(const Str *str, const char *cstr) {
	size_t i;

	i = 0;
	while (i < str->count && cstr[i]) {
		if (str->items[i] != cstr[i]) return false;
		i++;
	}
	return i == str->count && cstr[i] == '\0';
}

Str str_clone(const Str *str) {
	Str new_str;

	new_str = str_new(str->count);
	while (new_str.count < new_str.capacity) {
		new_str.items[new_str.count] = str->items[new_str.count];
		new_str.count++;
	}
	return new_str;
}

Str map_get_cstr(ListStr *keys, ListStr *vals, const char *key) {
	size_t i = 0;
	while (i < keys->count) {
		if (str_eq_cstr(&keys->items[i], key)) {
			return str_clone(&vals->items[i]);
		}
		i++;
	}
	return str_from("?");
}


Str map_get(ListStr *keys, ListStr *vals, char a, char b) {
	char key_str[3] = {a, b, '\0'};
	return map_get_cstr(keys, vals, key_str);
}

Str join(ListStr *list, char sep) {
	Str result;
	size_t total_len;
	size_t i ;
	size_t pos;
	char *joined;

	i = 0;
	total_len = 0;
	while (i < list->count) {
		total_len += list->items[i].count;
		if (i + 1 < list->count) {
			total_len += 1;
		}
		i++;
	}
	joined = (char *) malloc(total_len + 1);
	pos = 0;
	i = 0;
	while (i < list->count) {
		size_t j = 0;
		while (j < list->items[i].count) {
			joined[pos++] = list->items[i].items[j++];
		}

		if (i + 1 < list->count) {
			joined[pos++] = sep;
		}
		i++;
	}
	joined[pos] = '\0';
	result.items = joined;
	result.count = total_len;
	result.capacity = total_len;
	return result;
}
