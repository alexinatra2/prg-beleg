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

int deleteNode(node_t *node) {
  if (!node) {
    return 0;
  }
  deleteMedium(node->medium);
  free(node);
  return 0;
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

int lend(lib_t *lib, medium_t *medium, char *borrower) {
  if (!lib || !medium || !borrower) {
    return 0;
  }
  resetToRoot(lib);
  while (lib->current && !compareOnTitle(medium, lib->current->medium) &&
         !compareOnArtist(medium, lib->current->medium) &&
         !compareOnMediumType(medium, lib->current->medium)) {
    iterate(lib);
  }
  return lib->current ? lendMediumTo(lib->current->medium, borrower) : 0;
}

int removeMedium(lib_t *lib, medium_t *medium) {
  if (!lib || !medium || !lib->start) {
    return 0;
  }
  int comp = compareOn(medium, lib->start->medium, lib->filter_type);
  if (!comp) {
    node_t *next = lib->start->next;
    deleteNode(lib->start);
    lib->start = next;
  } else {
    lib->current = lib->start;
    node_t *previous;
    // first iteration always works, as initially lib->current = lib->start
    // and lib->start has been proven to exist
    do {
      previous = lib->current;
      iterate(lib);
      comp = lib->current
                 ? compareOn(medium, lib->current->medium, lib->filter_type)
                 : 1;
    } while (comp < 0);
    if (!comp) {
      node_t *previous_next = lib->current->next;
      deleteNode(lib->current);
      previous->next = previous_next;
    }
  }
  return comp == 0;
}

int resetToRoot(lib_t *lib) { return lib && (lib->current = lib->start); }

int iterate(lib_t *lib) {
  return lib && lib->current && (lib->current = lib->current->next);
}

lib_t *lookup(lib_t *lib, filter_type_e filter_type, char *search_string) {
  if (!lib) {
    return NULL;
  }
  medium_type_e medium_type = DVD;
  if (filter_type == MEDIUM_TYPE) {
    if (strcmp(search_string, "book")) {
      medium_type = BOOK;
    } else if (strcmp(search_string, "cd")) {
      medium_type = CD;
    }
  }
  medium_t *medium_dummy =
      createMedium(medium_type, search_string, search_string);
  lendMediumTo(medium_dummy, search_string);
  resetToRoot(lib);
  lib_t *lookup_lib = createLib(filter_type);
  do {
    if (!compareOn(medium_dummy, lib->current->medium, filter_type)) {
      insertMedium(lookup_lib, lib->current->medium);
    }
  } while (iterate(lib));
  return lookup_lib;
}

size_t getLibSize(lib_t *lib) {
  if (!lib || !resetToRoot(lib)) {
    return 0;
  }
  int size = 1;
  while (iterate(lib)) {
    size++;
  }
  return size;
}

char *libToString(lib_t *lib) {
  if (!lib->start) {
    return "EMPTY LIBRARY";
  }
  char *lib_string = malloc(228);
  sprintf(lib_string,
          "TYPE | %-32s | %-32s | %-32s\n"
          "-----|----------------------------------|---------------------------"
          "-------|----------------------------------\n",
          "TITLE", "ARTIST", "LENT TO");
  resetToRoot(lib);
  strcat(lib_string, mediumToString(lib->current->medium));
  while (iterate(lib)) {
    strcat(lib_string, "\n");
    strcat(lib_string, mediumToString(lib->current->medium));
  }
  return lib_string;
}
