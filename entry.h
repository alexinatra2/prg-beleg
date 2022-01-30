#ifndef ENTRY
#define ENTRY

typedef enum { NONE, GERMAN, ENGLISH } language_e;
typedef struct entry entry_t;

entry_t *createEntry(char *g, char *e);
int deleteEntry(entry_t *e);

char *getWord(entry_t *e, language_e lang);
int getGermanLength(entry_t *e);
int getEnglishLength(entry_t *e);

int compareEntries(entry_t *entry1, entry_t *entry2, language_e lang);

char *entryToString(entry_t *e);
char *formattedEntryToString(entry_t *e, language_e lang, int g_format, int e_format);

#endif // !ENTRY
