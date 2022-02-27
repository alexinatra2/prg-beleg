#include "library.h"
#include "medium.h"
#include "util.h"
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

int lend(lib_t *lib, int index, char *borrower) {
  if (!lib || !lib->start || index < 0 || index > getLibSize(lib)) {
    return 0;
  }
  if (index == 0) {
    lendMediumTo(lib->start->medium, borrower);
  } else {
    resetToRoot(lib);
    for (int i = 0; i < index; i++) {
      if (!iterate(lib)) {
        return 0;
      }
    }
    lendMediumTo(lib->current->medium, borrower);
  }
  return 1;
}

int removeMedium(lib_t *lib, int index) {
  if (!lib || !lib->start || index < 0 || index > getLibSize(lib)) {
    return 0;
  }
  if (index == 0) {
    node_t *second_element = lib->start->next;
    deleteNode(lib->start);
    lib->start = second_element;
  } else {
    resetToRoot(lib);
    node_t *previous;
    for (int i = 0; i < index; i++) {
      previous = lib->current;
      if (!iterate(lib)) {
        return 0;
      }
    }
    node_t *previous_next = lib->current->next;
    deleteNode(lib->current);
    previous->next = previous_next;
  }
  return 1;
}

int resetToRoot(lib_t *lib) { return lib && (lib->current = lib->start); }

int iterate(lib_t *lib) {
  return lib && lib->current && (lib->current = lib->current->next);
}

medium_t *currentMedium(lib_t *lib) {
  if (!lib || !lib->current) {
    return NULL;
  }
  return lib->current->medium;
}

lib_t *lookup(lib_t *lib, char *search_string) {
  if (!lib || !search_string) {
    return NULL;
  }
  lib_t *lookup_lib = createLib(lib->filter_type);
  char *trimmed_search_string = trim(search_string);
  resetToRoot(lib);
  medium_type_e medium_type = stringToMediumType(trimmed_search_string);
  medium_t *current;
  while (lib->current) {
    current = lib->current->medium;
    switch (lib->filter_type) {
    case MEDIUM_TYPE:
      if (medium_type == mediumTypeOf(current)) {
        insertMedium(lookup_lib, current);
      }
      break;
    case TITLE:
      if (strcmp(trimmed_search_string, titleOf(current))) {
        insertMedium(lookup_lib, current);
      }
      break;
    case ARTIST:
      if (strcmp(trimmed_search_string, artistOf(current))) {
        insertMedium(lookup_lib, current);
      }
      break;
    case BORROWER:
      if (strcmp(trimmed_search_string, borrowerOf(current))) {
        insertMedium(lookup_lib, current);
      }
      break;
    }
    iterate(lib);
  }
  return lookup_lib;
}

char *libToString(lib_t *lib) {
  if (!lib || !lib->start) {
    return "EMPTY LIBRARY";
  }
  char *lib_string = malloc(246);
  sprintf(lib_string,
          "INDEX | TYPE | %-32s | %-32s | %-32s\n"
          "------|------|----------------------------------|-------------------"
          "---------------|----------------------------------\n",
          "TITLE", "ARTIST", "LENT TO");
  resetToRoot(lib);
  int index = 0;
  do {
    // 3 characters for index and one for 0 termination
    char *index_string = malloc(9);
    sprintf(index_string, "%5d | ", index++);
    strcat(lib_string, index_string);
    strcat(lib_string, mediumToString(lib->current->medium));
    strcat(lib_string, "\n");
  } while (iterate(lib));

  char *order;
  switch (lib->filter_type) {
  case MEDIUM_TYPE:
    order = "medium type";
    break;
  case TITLE:
    order = "title";
    break;
  case ARTIST:
    order = "artist";
    break;
  default:
    order = "borrower";
    break;
  }
  strcat(lib_string, "\nordered by ");
  strcat(lib_string, order);
  return lib_string;
}
