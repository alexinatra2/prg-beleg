#ifndef DICT
#define DICT

#include "entry.h"

typedef struct dict dict_t;

dict_t *createDict(language_e);
int deleteDict(dict_t *d);

int insertEntry(dict_t *d, entry_t *e);
int removeEntry(dict_t *d, entry_t *e);

int insertEntryStr(dict_t *d, char *g, char *e);
int removeEntryStr(dict_t *d, char *g, char *e);

entry_t *nextEntry(dict_t *d);
int hasNextEntry(dict_t *d);

dict_t *lookup(dict_t *d, char *word);

int mergeDicts(dict_t *d1, dict_t *d2);

void printDict(dict_t *d);

#endif // !DICT
