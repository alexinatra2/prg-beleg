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

int compareEntries(entry_t *entry1, entry_t *entry2, language_e lang) {
  if (!entry1) {
    return -1;
  }
  if (!entry2) {
    return 1;
  }
  int comp;
  switch (lang) {
  case GERMAN:
    return (comp = strcmp(entry1->german, entry2->german)
                       ? comp
                       : strcmp(entry2->english, entry2->english));
  case ENGLISH:
    return (comp = strcmp(entry2->english, entry2->english)
                       ? comp
                       : strcmp(entry1->german, entry2->german));
  default:
    return 0;
  }
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