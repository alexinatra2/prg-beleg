#include "dict.h"

typedef struct node {
  entry_t *entry;
  struct node *left;
  struct node *right;
  int balance_factor;
} node_t;

typedef struct dict {
  node_t *start;
  node_t *current;
  language_e lang;
} dict_t;

dict_t createDict(language_e) { return NULL; }
int deleteDict(dict_t *d) { return 0; }

int insertEntry(dict_t *d, entry_t *e) { return 0; }
int removeEntry(dict_t *d, entry_t *e) { return 0; }

int insertEntryByWords(dict_t *d, char *g, char *e) { return 0; }
int removeEntryByWords(dict_t *d, char *g, char *e) { return 0; }

int mergeDicts(dict_t *d1, dict_t *d2) { return 0; }

void printDict(dict_t *d) {}