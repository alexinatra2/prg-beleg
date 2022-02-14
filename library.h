#ifndef LIBRARY_H
#define LIBRARY_H

#include "medium.h"

typedef struct lib lib_t;

lib_t *createLib(filter_type_e filter_type);
int deleteLib(lib_t *lib);

int insertMedium(lib_t *lib, medium_t *medium);
int removeMedium(lib_t *lib, medium_t *medium);

lib_t *lookup(lib_t *lib, filter_type_e filter_type, char *search_string);

int resetToRoot(lib_t *lib);
int iterate(lib_t *lib);

char *libToString(lib_t *lib);

#endif // !LIBRARY_H