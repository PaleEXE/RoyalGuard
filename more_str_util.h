#ifndef MORE_STR_UTIL_H
#define MORE_STR_UTIL_H

#include "str.h"
#include "list_str.h"
#include <stdbool.h>

bool str_eq_cstr(const Str *str, const char* cstr);

Str str_clone(const Str *str);

Str map_get(ListStr *keys, ListStr *vals, char a, char b);

Str join(ListStr *list, char sep);

#endif //MORE_STR_UTIL_H
