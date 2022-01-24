#include "entry.h"
#include <stdlib.h>

typedef struct entry {
  char *german;
  char *english;
} entry_t;

entry_t *createEntry(char *g, char *e) { return NULL; }
int deleteEntry(entry_t *e) { return 0; }

void printEntry(entry_t *e) {}