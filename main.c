#include <stdio.h>

#include "parser.h"
#include "str.h"
#include "list_str.h"
#include "more_str_util.h"

Str convert(ListStr *segments, ListStr *num_key, ListStr *num_val, ListStr *scl_val) {
	ListStr words;
	Str result;
	Str h_word;
	Str u_word;
	Str t_word;
	Str scale;
	Str joined;
	size_t scale_index;
	size_t i;
	char h;
	char t;
	char u;

	words = list_Str_new(10);
	i = 0;
	while (i < segments->count) {
		Str segment = segments->items[i];
		if (str_eq_cstr(&segment, "000")) {
			i++;
			continue;
		}
		ListStr part = list_Str_new(5);
		h = segment.items[0];
		t = segment.items[1];
		u = segment.items[2];
		if (h != '0') {
			h_word = map_get(num_key, num_val, h, '\0');
			list_Str_append(&part, h_word);
			list_Str_append(&part, str_from("hundred"));
		}
		if (t == '0') {
			if (u != '0') {
				u_word = map_get(num_key, num_val, u, '\0');
				list_Str_append(&part, u_word);
			}
		} else if (t == '1') {
			char teen[3] = {t, u, '\0'};
			Str tword = map_get(num_key, num_val, teen[0], teen[1]);
			list_Str_append(&part, tword);
		} else {
			char tens[3] = {t, '0', '\0'};
			t_word = map_get(num_key, num_val, tens[0], tens[1]);
			list_Str_append(&part, t_word);
			if (u != '0') {
				u_word = map_get(num_key, num_val, u, '\0');
				list_Str_append(&part, u_word);
			}
		}
		scale_index = segments->count - i - 1;
		if (scale_index > 0 && scale_index < scl_val->count) {
			scale = scl_val->items[scale_index];
			list_Str_append(&part, scale);
		}

		joined = join(&part, ' ');
		list_Str_append(&words, joined);
		list_Str_free(&part);
		i++;
	}

	if (words.count == 0)
		return str_from("zero");

	result = join(&words, ' ');
	list_Str_free(&words);
	return result;
}

int main(int argc, char **argv) {
	ListStr num_key, num_val, scl_key, scl_val;
	char *num, *file_path;

	if (argc < 2 || argc > 3) {
		fwrite("Error\n", 1, 6, stdout);
		return -1;
	}
	num = argv[1];
	file_path = "numbers.dict";
	if (argc == 3) {
		num = argv[2];
		file_path = argv[1];
	}
	num_key = list_Str_new(8);
	num_val = list_Str_new(8);
	scl_key = list_Str_new(8);
	scl_val = list_Str_new(8);
	file_parse(file_path, &num_key, &num_val, &scl_key, &scl_val);
	ListStr lst = input_parse(num);
	Str conv = convert(&lst, &num_key, &num_val, &scl_val);
	str_print(&conv);
	putchar('\n');
	return 0;
}
