#ifndef ENTRY
#define ENTRY

typedef enum { NONE, GERMAN, ENGLISH } language_e;
typedef struct entry entry_t;

entry_t *createEntry(char *g, char *e);
int deleteEntry(entry_t *e);

int compareEntries(entry_t *e1, entry_t *e2, language_e lang);

char *entryToString(entry_t *e, language_e lang);

#endif // !ENTRY
