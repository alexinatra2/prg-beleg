#include "entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry {
  char *german;
  char *english;
} entry_t;

entry_t *createEntry(char *g, char *e) {
  entry_t *entry = malloc(sizeof(entry_t));
  if (entry) {
    entry->german = g;
    entry->english = e;
  }
  return entry;
}

int deleteEntry(entry_t *entry) {
  if (entry) {
    free(entry);
    return 1;
  }
  return 0;
}

char *entryToString(entry_t *entry, language_e lang) {
  if (entry) {
    // strlen("entry1 : entry2") + terminating 0-byte
    char *str = malloc(strlen(entry->german) + strlen(entry->english) + 4);
    if (str) {
      switch (lang) {
      case GERMAN:
        sprintf(str, "%s : %s", entry->german, entry->english);
        break;
      case ENGLISH:
      default:
        sprintf(str, "%s : %s", entry->english, entry->german);
      }
    }
    return str;
  }
  return NULL;
}