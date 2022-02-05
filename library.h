#ifndef LIBRARY_H
#define LIBRARY_H

#include "medium.h"

typedef struct lib lib_t;

lib_t *createLib(void);
int deleteLib(lib_t *lib);

int insertMedium(lib_t *lib, medium_t *medium);
int removeMedium(lib_t *lib, medium_t *medium);

lib_t *lookup(lib_t *lib, filter_type_e filter_type, char *search_string);

char *libToString(lib_t *lib);

#endif // !LIBRARY_H