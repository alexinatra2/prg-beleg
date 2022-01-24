#include "dict.h"
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
      printf("deleting (%s)", entryToString(node->entry, NONE));
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

int insertEntry(dict_t *d, entry_t *e) {
  if (d) {
    node_t *node = createNode(e);
    if (node) {
      d->current = d->start;
      while (d->current) {
      }
      return 1;
    }
  }
  return 0;
}

int removeEntry(dict_t *d, entry_t *e) { return 0; }

int insertEntryByWords(dict_t *d, char *g, char *e) { return 0; }
int removeEntryByWords(dict_t *d, char *g, char *e) { return 0; }

int mergeDicts(dict_t *d1, dict_t *d2) { return 0; }

void printDict(dict_t *d) {}