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
  int (*compareFunction)(medium_t *, medium_t *);
} lib_t;

lib_t *createLib(filter_type_e filter_type) {
  lib_t *new_lib = malloc(sizeof(lib_t));
  if (!new_lib) {
    return NULL;
  }
  new_lib->start = NULL;
  new_lib->current = NULL;
  return new_lib;
}

int deleteLib(lib_t *lib){
    if (!lib) {
        return 0;
    }
    node_t *temp;
    lib->current = lib->start;
    while (lib->current) {
        temp = lib->current;
        lib->current = lib->current->next; 
        free(temp); 
    }
    free(lib);
    return 1;
}

int insertMedium(lib_t *lib, medium_t *medium) { 
    if (!lib || !medium) {
        return 0;
    }
    lib->current = lib->start;
    while (lib->current) {
        lib->current = lib->current->next;
    }
    return 0;
}

int removeMedium(lib_t *lib, medium_t *medium) { return 0; }

lib_t *lookup(lib_t *lib, filter_type_e filter_type, char *search_string) {
  return NULL;
}
char *libToString(lib_t *lib) { return ""; }
