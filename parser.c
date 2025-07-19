#include "parser.h"
#include "str.h"
#include "list_str.h"
#include "str_util.h"

#include <stdio.h>

void put_kv(ListStr *num_key, ListStr *num_val, ListStr *scl_key,
			ListStr *scl_val, ListStr line) {
	Str k;
	Str v;

	if (line.count != 2) {
		fwrite("Dict Error\n", 1, 11, stdout);
		exit(-1);
	}
	k = trim(&line.items[0]);
	v = trim(&line.items[1]);
	if (k.count > 2) {
		list_Str_append(scl_key, k);
		list_Str_append(scl_val, v);
	} else {
		list_Str_append(num_key, k);
		list_Str_append(num_val, v);
	}
}

void file_parse(const char *file_path, ListStr *num_key,
				ListStr *num_val, ListStr *scl_key, ListStr *scl_val) {
	ListStr lines;
	ListStr line;
	Str content;
	size_t i;

	content = read_file(file_path);
	if (content.count == 0) {
		fwrite("Dict Error\n", 1, 11, stdout);
		exit(-1);
	}
	lines = split(&content, '\n');
	i = 0;
	while (i < lines.count) {
		line = split(&lines.items[i], ':');
		if (line.count == 0) {
			i++;
			continue;
		}
		put_kv(num_key, num_val, scl_key, scl_val, line);
		i++;
		free(line.items);
	}
	free(content.items);
	list_Str_free(&lines);
}

ListStr input_parse(const char *input) {
	ListStr result;
	Str str;
	Str pad;
	Str seg;
	size_t i;

	i = 0;
	while (input[i]) {
		if (input[i] < '0' || input[i] > '9') {
			fwrite("Error\n", 1, 6, stdout);
			exit(-1);
		}
		i++;
	}
	result = list_Str_new(9);
	str = str_from(input);
	pad = pad_zeros(&str);
	i = 0;

	while (i < pad.count) {
		seg = str_new(3);
		seg.count = 3;
		seg.items[0] = pad.items[i + 0];
		seg.items[1] = pad.items[i + 1];
		seg.items[2] = pad.items[i + 2];
		list_Str_append(&result, seg);
		i += 3;
	}
	free(str.items);
	free(pad.items);
	return result;
}
