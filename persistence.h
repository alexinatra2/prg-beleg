#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "library.h"

lib_t *loadFrom(char *file_name);
int saveTo(char *file_name, lib_t *lib);

#endif // !PERSISTENCE_H
