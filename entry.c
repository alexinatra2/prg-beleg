#include "entry.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry {
  char *german;
  char *english;
} entry_t;

char *trimWhitespace(char *str) {
  char *end;
  while (isspace((unsigned char)*str)) {
    str++;
  }
  if (*str == 0)
    return str;
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;
  end[1] = '\0';
  return str;
}

entry_t *createEntry(char *g, char *e) {
  entry_t *entry = malloc(sizeof(entry_t));
  if (entry) {
    char *trimmed_g = trimWhitespace(g);
    entry->german = malloc(strlen(trimmed_g) + 1);
    if (entry->german) {
      strcpy(entry->german, trimmed_g);
    }
    char *trimmed_e = trimWhitespace(e);
    entry->english = malloc(strlen(trimmed_e) + 1);
    if (entry->english) {
      strcpy(entry->english, trimmed_e);
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

char *entryToString(entry_t *entry) {
  if (entry) {
    // strlen("entry1 | entry2") + terminating 0-byte
    char *str = malloc(strlen(entry->german) + strlen(entry->english) + 4);
    if (str) {
      sprintf(str, "%s, %s", entry->german, entry->english);
    }
    return str;
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