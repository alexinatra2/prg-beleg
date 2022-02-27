#ifndef LIBRARYIO_H
#define LIBRARYIO_H
#include "library.h"
#include "medium.h"

lib_t *importLib(char *file_name, filter_type_e filter_type);
int exportLib(lib_t *lib, char *file_name);

#endif // !LIBRARYIO_H