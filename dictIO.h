#ifndef DICT_IO
#define DICT_IO

#include "dict.h"
#include "entry.h"

dict_t *importDict(char *file_name, language_e lang);
int exportDict(dict_t *d);

#endif // !DICT_IO