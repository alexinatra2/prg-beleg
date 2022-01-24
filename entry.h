typedef struct entry entry_t;

entry_t *createEntry(char *g, char *e);
int deleteEntry(entry_t *e);

void printEntry(entry_t *e);