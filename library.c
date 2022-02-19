#include "library.h"

#include "medium.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  medium_t *medium;
  struct node *next;
} node_t;

typedef struct lib {
  node_t *start;
  node_t *current;
  filter_type_e filter_type;
} lib_t;

lib_t *createLib(filter_type_e filter_type) {
  lib_t *new_lib = malloc(sizeof(lib_t));
  if (!new_lib) {
    return NULL;
  }
  new_lib->start = NULL;
  new_lib->current = NULL;
  new_lib->filter_type = filter_type;
  return new_lib;
}

int deleteLib(lib_t *lib) {
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

node_t *createNode(medium_t *medium, node_t *next) {
  if (!medium) {
    return NULL;
  }
  node_t *new_node = malloc(sizeof(node_t));
  if (!new_node) {
    return NULL;
  }
  new_node->medium = medium;
  new_node->next = next;
  return new_node;
}

int insertMedium(lib_t *lib, medium_t *medium) {
  if (!lib || !medium) {
    return 0;
  }
  medium_t *cloned_medium = cloneMedium(medium);
  if (!lib->start) {
    lib->start = createNode(cloned_medium, NULL);
    return 1;
  }
  int comp = compareOn(cloned_medium, lib->start->medium, lib->filter_type);
  if (comp < 0) {
    lib->start = createNode(cloned_medium, lib->start);
  } else {
    lib->current = lib->start;
    node_t *previous;
    // first iteration always works, as initially lib->current = lib->start
    // and lib->start has been proven to exist
    do {
      previous = lib->current;
      iterate(lib);
      comp = lib->current ? compareOn(cloned_medium, lib->current->medium,
                                      lib->filter_type)
                          : -1;
    } while (comp > 0);
    if (comp) {
      previous->next = createNode(cloned_medium, lib->current);
    }
  }
  return comp != 0;
}

int lend(lib_t *lib, medium_t *medium, char *borrower) { return 0; }

int removeMedium(lib_t *lib, medium_t *medium) { return 0; }

int resetToRoot(lib_t *lib) { return lib && (lib->current = lib->start); }

int iterate(lib_t *lib) {
  return lib && lib->current && (lib->current = lib->current->next);
}

lib_t *lookup(lib_t *lib, filter_type_e filter_type, char *search_string) {
  return NULL;
}

size_t getLibSize(lib_t *lib) {
  if (!lib || !resetToRoot(lib)) {
    return 0; // nothing to print
  }
  int size = strlen(mediumToString(lib->current->medium));
  while (iterate(lib)) {
    size += strlen(mediumToString(lib->current->medium)) + 1; // new line
  }
  return size + 1; // 0 terminated
}

char *libToString(lib_t *lib) {
  int size = getLibSize(lib);
  if (!size) {
    return NULL;
  }
  char *lib_string = malloc(size);
  resetToRoot(lib);
  strcat(lib_string, mediumToString(lib->current->medium));
  while (iterate(lib)) {
    strcat(lib_string, "\n");
    strcat(lib_string, mediumToString(lib->current->medium));
  }
  return lib_string;
}
