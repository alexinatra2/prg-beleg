#include "dict.h"
#include "entry.h"
#include <stdio.h>
#include <stdlib.h>

extern int LOGGING;

typedef struct node {
  entry_t *entry;
  struct node *left;
  struct node *right;
  int balance_factor;
} node_t;

typedef struct dict {
  node_t *start;
  node_t *current;
  language_e lang;
} dict_t;

node_t *createNode(entry_t *entry) {
  node_t *node = malloc(sizeof(node_t));
  if (node) {
    node->entry = entry;
    node->left = NULL;
    node->right = NULL;
    node->balance_factor = 0;
  }
  return node;
}

void deleteNode(node_t *node) {
  if (node) {
    if (LOGGING) {
      printf("deleting (%s)\n", entryToString(node->entry, NONE));
    }
    deleteNode(node->left);
    deleteNode(node->right);
    free(node);
  }
}

dict_t *createDict(language_e lang) {
  dict_t *dict = malloc(sizeof(dict_t));
  if (dict) {
    dict->start = NULL;
    dict->current = NULL;
    dict->lang = lang;
  }
  return dict;
}

int deleteDict(dict_t *d) {
  if (d) {
    deleteNode(d->start);
    free(d);
    return 1;
  }
  return 0;
}

void resetToRoot(dict_t *d) { d->current = d->start; }

void traverseLeft(dict_t *d) {
  if (LOGGING) {
    printf("going left");
  }
  d->current = d->current->left;
}

void traverseRight(dict_t *d) {
  if (LOGGING) {
    printf("going right");
  }
  d->current = d->current->right;
}

int insertEntry(dict_t *d, entry_t *e) {
  if (d) {
    node_t *node = createNode(e);
    if (node) {
      if (!d->start) {
        d->start = node;
        return 1;
      }
      resetToRoot(d);
      int comp;
      while (d->current) {
        comp = compareEntries(e, d->current->entry, d->lang);
        if (comp < 0) {
          traverseLeft(d);
        } else if (comp > 0) {
          traverseRight(d);
        } else {
          if (LOGGING) {
            printf("entry already present (%s)\n", entryToString(e, d->lang));
          }
          return 0;
        }
      }
      d->current = node;
      return 1;
    }
  }
  return 0;
}

int removeEntry(dict_t *d, entry_t *e) { return 0; }

int insertEntryByWords(dict_t *d, char *g, char *e) { return 0; }
int removeEntryByWords(dict_t *d, char *g, char *e) { return 0; }

int mergeDicts(dict_t *d1, dict_t *d2) { return 0; }

void printNode(node_t *n, language_e lang) {
  if (n && n->entry) {
    printf("%s\n", entryToString(n->entry, lang));
    printNode(n->left, lang);
    printNode(n->right, lang);
  }
}

void printDict(dict_t *d) {
  printf("--- %s - %s ---\n", d->lang == GERMAN ? "GERMAN" : "ENGLISH",
         d->lang == ENGLISH ? "GERMAN" : "ENGLISH");
  if (d) {
    printNode(d->start, d->lang);
  }
  printf("------------------------\n");
}