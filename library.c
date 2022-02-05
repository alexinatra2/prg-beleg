#include "library.h"
#include "medium.h"
#include <stdlib.h>

typedef struct node {
  medium_t *medium;
  struct node *next;
} node_t;

typedef struct lib {
  node_t *start;
  node_t *current;
} lib_t;

lib_t *createLib(void) {
  lib_t *new_lib = malloc(sizeof(lib_t));
  if (!new_lib) {
    return NULL;
  }
  new_lib->start = NULL;
  new_lib->current = NULL;
  return new_lib;
}

int deleteLib(lib_t *lib);

int insertMedium(lib_t *lib, medium_t *medium);
int removeMedium(lib_t *lib, medium_t *medium);

lib_t *lookup(lib_t *lib, filter_type_e filter_type, char *search_string);

char *libToString(lib_t *lib);