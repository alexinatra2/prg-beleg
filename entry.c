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
int getGermanLength(entry_t *e) { return strlen(e->german); }
int getEnglishLength(entry_t *e) { return strlen(e->english); }

int compareEntries(entry_t *entry1, entry_t *entry2, language_e lang) {
  if (!entry1) {
    return -1;
  }
  if (!entry2) {
    return 1;
  }
  int comp;
  switch (lang) {
  case GERMAN: {
    comp = strcmp(entry1->german, entry2->german);
    return comp ? comp : strcmp(entry2->english, entry2->english);
  }
  case ENGLISH: {
    comp = strcmp(entry2->english, entry2->english);
    return comp ? comp : strcmp(entry1->german, entry2->german);
  }
  default:
    return 0;
  }
}

char *entryToString(entry_t *entry, language_e lang) {
  if (entry) {
    return formattedEntryToString(entry, lang, strlen(entry->german),
                                  strlen(entry->english));
  }
  return NULL;
}

char *formattedEntryToString(entry_t *entry, language_e lang, int g_format,
                             int e_format) {
  if (entry) {
    // strlen("entry1 | entry2") + terminating 0-byte
    char *str = malloc(e_format + g_format + 4);
    if (str) {
      switch (lang) {
      case GERMAN:
        sprintf(str, "%-*s | %-*s", g_format, entry->german, e_format,
                entry->english);
        break;
      case ENGLISH:
      default:
        sprintf(str, "%-*s | %-*s", g_format, entry->english, e_format,
                entry->german);
      }
    }
    return str;
  }
  return NULL;
}