#include "dict.h"
#include "entry.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GERMAN_STR "GERMAN"
#define ENGLISH_STR "ENGLISH"

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
    if (VERBOSE_LOGGING) {
      printf("dict %d: deleting (%s)\n", dict->id,
             entryToString(node->entry, NONE));
    }
    deleteNodes(dict, node->next);
    free(node);
  }
}

void deleteNode(dict_t *dict, node_t *node) {
  if (dict && node) {
    if (VERBOSE_LOGGING) {
      printf("dict %d: deleting (%s)\n", dict->id,
             entryToString(node->entry, NONE));
    }
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
      d->current = d->current->next;
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
      d->current = d->current->next;
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

int mergeDicts(dict_t *d1, dict_t *d2) {
  return d1 && d2 ? insertNodes(d1, d2->start) : 0;
}

void printNode(node_t *n, language_e lang, int g_format, int e_format) {
  if (n && n->entry) {
    printf("| %s |\n",
           formattedEntryToString(n->entry, lang, g_format, e_format));
    printNode(n->next, lang, g_format, e_format);
  }
}

void updateFormat(dict_t *d) {
  if (d) {
    resetToRoot(d);
    d->g_format = strlen(GERMAN_STR);
    d->e_format = strlen(ENGLISH_STR);
    int ger_current;
    int eng_current;
    while (d->current) {
      ger_current = getGermanLength(d->current->entry);
      eng_current = getEnglishLength(d->current->entry);
      d->g_format = d->g_format > ger_current ? d->g_format : ger_current;
      d->e_format = d->e_format > eng_current ? d->e_format : eng_current;
      d->current = d->current->next;
    }
  }
}

void printTableSeparator(dict_t *d) {
  if (d) {
    for (int i = 0; i < d->g_format + d->e_format + 7; i++) {
      printf("-");
    }
    printf("\n");
  }
}

void printDict(dict_t *d) {
  printf("\ndict %d:\n", d->id);
  updateFormat(d);
  printTableSeparator(d);
  printf("| %-*s | %-*s |\n", d->lang == GERMAN ? d->g_format : d->e_format,
         d->lang == GERMAN ? GERMAN_STR : ENGLISH_STR,
         d->lang == GERMAN ? d->e_format : d->g_format,
         d->lang == ENGLISH ? GERMAN_STR : ENGLISH_STR);
  printTableSeparator(d);
  if (d) {
    printNode(d->start, d->lang, d->g_format, d->e_format);
  }
  printTableSeparator(d);
}