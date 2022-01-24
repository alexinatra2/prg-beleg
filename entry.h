typedef enum { NONE, GERMAN, ENGLISH } language_e;
typedef struct entry entry_t;

entry_t *createEntry(char *g, char *e);
int deleteEntry(entry_t *e);

char *entryToString(entry_t *e, language_e lang);