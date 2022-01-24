#include "entry.h"
#include "logging.h"
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
    entry->german = malloc(strlen(g) + 1);
    if (entry->german) {
      strcpy(entry->german, g);
    }
    entry->english = malloc(strlen(e) + 1);
    if (entry->english) {
      strcpy(entry->english, e);
    }
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
    if (LOGGING) {
      printf("entry1 does not exist\n");
    }
    return -1;
  }
  if (!entry2) {
    if (LOGGING) {
      printf("entry2 does not exist\n");
    }
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
    if (LOGGING) {
      printf("neither german nor english were selected\n");
    }
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