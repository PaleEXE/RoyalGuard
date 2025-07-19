#ifndef STR_UTIL_H
#define STR_UTIL_H

#include "str.h"
#include "list_str.h"

Str concat(const Str *str0, const Str *str1);

Str pad_zeros(Str *str);

Str trim(const Str *input);

Str read_file(const char *file_path);

ListStr split(const Str *input, char delim);

#endif //STR_UTIL_H
