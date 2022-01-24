#ifndef DICT
#define DICT

#include "entry.h"

typedef struct node node_t;
typedef struct dict dict_t;

dict_t *createDict(language_e);
int deleteDict(dict_t *d);

int insertEntry(dict_t *d, entry_t *e);
int removeEntry(dict_t *d, entry_t *e);

int insertEntryByWords(dict_t *d, char *g, char *e);
int removeEntryByWords(dict_t *d, char *g, char *e);

int mergeDicts(dict_t *d1, dict_t *d2);

void printDict(dict_t *d);

#endif // !DICT
