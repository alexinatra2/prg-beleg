#include "dict.h"
#include "entry.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DICT_CONSTANTS
#define DICT_CONSTANTS
#define GERMAN_STR "GERMAN"
#define ENGLISH_STR "ENGLISH"
#define TOTAL_TABLE_PADDING 7
#endif // !DICT_CONSTANTS

typedef struct node {
  entry_t *entry;
  struct node *next;
} node_t;

typedef struct dict {
  int g_format;
  int e_format;
  char *description;
  node_t *start;
  node_t *current;
  language_e lang;
} dict_t;

node_t *createNode(entry_t *entry, node_t *next) {
  node_t *node = malloc(sizeof(node_t));
  if (node) {
    node->entry = entry;
    node->next = next;
  }
  return node;
}

void deleteNodes(dict_t *dict, node_t *node) {
  if (dict && node) {
    deleteNodes(dict, node->next);
    free(node);
  }
}

void deleteNode(dict_t *dict, node_t *node) {
  if (dict && node) {
    free(node);
  }
}

dict_t *createDict(language_e lang, char *description) {
  dict_t *dict = malloc(sizeof(dict_t));
  if (dict) {
    dict->start = NULL;
    dict->current = NULL;
    dict->lang = lang;
    dict->description = description;
  }
  return dict;
}

int deleteDict(dict_t *d) {
  if (d) {
    deleteNodes(d, d->start);
    free(d);
    return 1;
  }
  return 0;
}

void resetToRoot(dict_t *d) { d->current = d->start; }
void iterateDict(dict_t *d) { d->current = d->current->next; }
int currentExists(dict_t *d) { return d && d->current; }
entry_t *getCurrent(dict_t *d) {
  return d && d->current ? d->current->entry : NULL;
}

int insertEntry(dict_t *d, entry_t *e) {
  if (!d || !e) {
    return 0;
  }
  if (!d->start) {
    d->start = createNode(e, NULL);
    return 1;
  }
  int comp = compareEntries(e, d->start->entry, d->lang);
  if (comp < 0) {
    d->start = createNode(e, d->start);
  } else {
    resetToRoot(d);
    node_t *previous;
    // first iteration always works, as initially d->current = d->start
    // and d->start has been proven to exist
    do {
      previous = d->current;
      iterateDict(d);
      comp = d->current ? compareEntries(e, d->current->entry, d->lang) : -1;
    } while (comp > 0);
    if (comp) {
      previous->next = createNode(e, d->current);
    }
  }
  return comp != 0;
}

int removeEntry(dict_t *d, entry_t *e) {
  if (!d || !e || !d->start) {
    return 0;
  }
  int comp = compareEntries(e, d->start->entry, d->lang);
  node_t *previous;
  if (!comp) {
    previous = d->start;
    d->start = d->start->next;
    deleteNode(d, previous);
  } else {
    resetToRoot(d);
    do {
      previous = d->current;
      iterateDict(d);
      comp = d->current ? compareEntries(e, d->current->entry, d->lang) : -1;
    } while (comp > 0);
    if (!comp) {
      previous->next = d->current->next;
      deleteNode(d, d->current);
    }
  }
  return !comp;
}

int insertEntryStr(dict_t *d, char *g, char *e) {
  return insertEntry(d, createEntry(g, e));
}

int removeEntryStr(dict_t *d, char *g, char *e) {
  return removeEntry(d, createEntry(g, e));
}

dict_t *lookup(dict_t *d, char *word) {
  if (!d) {
    return NULL;
  }
  word = trimWhitespace(word);
  resetToRoot(d);
  char *description_str = malloc(strlen(word) + 16);
  sprintf(description_str, "Occurences of \"%s\"", word);
  dict_t *word_dict = createDict(d->lang, description_str);
  if (!word_dict) {
    return NULL;
  }
  while (d->current) {
    if (strcmp(getWord(d->current->entry, d->lang), word) == 0) {
      insertEntry(word_dict, cloneEntry(d->current->entry));
    }
    iterateDict(d);
  }
  return word_dict;
}

int insertNodes(dict_t *d, node_t *n) {
  return !n || (insertEntry(d, n->entry) && insertNodes(d, n->next));
}

int mergeDicts(dict_t *d1, dict_t *d2) {
  return d1 && d2 ? insertNodes(d1, d2->start) : 0;
}

void printNodes(node_t *n, language_e lang, int g_format, int e_format) {
  if (!n || !n->entry) {
    return;
  }
  entry_t *entry = n->entry;
  printf("| %-*s | %-*s |\n", lang == GERMAN ? g_format : e_format,
         getWord(entry, lang), lang == GERMAN ? e_format : g_format,
         getWord(entry, lang == GERMAN ? ENGLISH : GERMAN));
  printNodes(n->next, lang, g_format, e_format);
}

void updateFormat(dict_t *d) {
  if (!d) {
    return;
  }
  resetToRoot(d);
  d->g_format = strlen(GERMAN_STR);
  d->e_format = strlen(ENGLISH_STR);
  int ger_current, eng_current;
  while (d->current) {
    ger_current = strlen(getWord(d->current->entry, GERMAN));
    eng_current = strlen(getWord(d->current->entry, ENGLISH));
    d->g_format = d->g_format > ger_current ? d->g_format : ger_current;
    d->e_format = d->e_format > eng_current ? d->e_format : eng_current;
    iterateDict(d);
  }
}

char *tableSeparator(dict_t *d, int g_format, int e_format) {
  if (!d) {
    return NULL;
  }
  int separators = g_format + e_format + TOTAL_TABLE_PADDING + 1;
  char *table_separator = malloc(separators);
  for (int i = 0; i < separators; i++) {
    table_separator[i] = '-';
  }
  table_separator[separators - 1] = 0;
  return table_separator;
}

void printDict(dict_t *d) {
  if (!d) {
    return;
  }
  updateFormat(d);
  char *table_separator = tableSeparator(d, d->g_format, d->e_format);
  printf("\n%s:\n"
         "%s\n"
         "| %-*s | %-*s |\n"
         "%s\n",
         d->description ? d->description : "dictionary", table_separator,
         d->lang == GERMAN ? d->g_format : d->e_format,
         d->lang == GERMAN ? GERMAN_STR : ENGLISH_STR,
         d->lang == GERMAN ? d->e_format : d->g_format,
         d->lang == GERMAN ? ENGLISH_STR : GERMAN_STR, table_separator);
  if (d) {
    printNodes(d->start, d->lang, d->g_format, d->e_format);
  }
  printf("%s\n", table_separator);
}