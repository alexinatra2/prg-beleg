#include "dict.h"
#include "entry.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  entry_t *entry;
  struct node *next;
} node_t;

typedef struct dict {
  int id;
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

void printNode(node_t *n, language_e lang) {
  if (n && n->entry) {
    printf("%s\n", entryToString(n->entry, lang));
    printNode(n->next, lang);
  }
}

void printDict(dict_t *d) {
  printf("\ndict %d:\n", d->id);
  printf("--- %s - %s ---\n", d->lang == GERMAN ? "GERMAN" : "ENGLISH",
         d->lang == ENGLISH ? "GERMAN" : "ENGLISH");
  if (d) {
    printNode(d->start, d->lang);
  }
  printf("------------------------\n\n");
}