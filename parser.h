//
// Created by VICTUS on 7/19/2025.
//

#ifndef PARSER_H
#define PARSER_H

#include "list_str.h"

void file_parse(const char *file_path, ListStr *num_key,
				ListStr *num_val, ListStr *scl_key, ListStr *scl_val);

ListStr input_parse(const char *input);

#endif //PARSER_H
