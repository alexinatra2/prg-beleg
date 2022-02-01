#include "dict.h"
#include "entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DICT_CONSTANTS
#define DICT_CONSTANTS
#define GERMAN_STR "GERMAN"
#define ENGLISH_STR "ENGLISH"
#define MAX_TABLE_SEPARATOR                                                    \
  "--------------------------------------------------------------------------" \
  "--------------------------------------------------------------------------" \
  "------------------------------------------------------------------------"
#define TOTAL_TABLE_PADDING 7
#endif // !DICT_CONSTANTS

typedef struct node {
  entry_t *entry;
  struct node *next;
} node_t;

typedef struct dict {
  int id;
  int g_format;
  int e_format;
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

dict_t *createDict(language_e lang) {
  dict_t *dict = malloc(sizeof(dict_t));
  if (dict) {
    dict->start = NULL;
    dict->current = NULL;
    dict->lang = lang;
    static int id_counter = 1;
    dict->id = id_counter++;
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

int insertNodes(dict_t *d, node_t *n) {
  return !n || (insertEntry(d, n->entry) && insertNodes(d, n->next));
}

entry_t *nextEntry(dict_t *d) {
  if (!d) {
    return NULL;
  }
  static int position = 0;
  if (position == 0) {
    resetToRoot(d);
    position++;
    return d->start->entry;
  } else if (hasNext(d)) {
    iterateDict(d);
    return d->current->entry;
  }
  position = 0;
  return NULL;
}

int hasNext(dict_t *d) { return d && d->current && d->current->next; }

dict_t *lookup(dict_t *d, char *word) {
  if (!d) {
    return NULL;
  }
  resetToRoot(d);
  dict_t *word_dict = createDict(d->lang);
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

char *tableSeparator(dict_t *d) {
  if (!d) {
    return NULL;
  }
  int str_length = d->g_format + d->e_format + TOTAL_TABLE_PADDING;
  char *str = malloc(str_length);
  if (str) {
    strncpy(str, MAX_TABLE_SEPARATOR, str_length);
  }
  return str;
}

void printDict(dict_t *d) {
  if (!d) {
    return;
  }
  updateFormat(d);
  char *table_separator = tableSeparator(d);
  printf("\ndict %d:\n"
         "%s\n"
         "| %-*s | %-*s |\n"
         "%s\n",
         d->id, table_separator, d->lang == GERMAN ? d->g_format : d->e_format,
         d->lang == GERMAN ? GERMAN_STR : ENGLISH_STR,
         d->lang == GERMAN ? d->e_format : d->g_format,
         d->lang == GERMAN ? ENGLISH_STR : GERMAN_STR, table_separator);
  if (d) {
    printNodes(d->start, d->lang, d->g_format, d->e_format);
  }
  printf("%s\n", tableSeparator(d));
}