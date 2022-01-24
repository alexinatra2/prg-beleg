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
  node_t *root;
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
    dict->root = NULL;
    dict->current = NULL;
    dict->lang = lang;
  }
  return dict;
}

int deleteDict(dict_t *d) {
  if (d) {
    deleteNode(d->root);
    free(d);
    return 1;
  }
  return 0;
}

int signum(int number) {
  if (number < 0) {
    return -1;
  }
  if (number > 0) {
    return 1;
  }
  return 0;
}

void iterate(node_t *n, int balance_factor) {
  switch (signum(balance_factor)) {
  case -1:
    n = n->left;
    break;
  case 1:
    n = n->right;
  }
}

int rotate(node_t *n);
int balance(node_t *n);

int insertEntry(dict_t *d, entry_t *e) {
  if (d) {
    d->current = d->root;
    node_t *temp_node;
    printDict(d);
    while (d->current) {
      iterate(d->current, compareEntries(e, d->current->entry, d->lang));
    }
    d->current = createNode(e);
    return 1;
  }
  if (LOGGING) {
    printf("trying to insert an entry into unallocated dict.\n");
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
  } else {
    if (LOGGING) {
      printf("trying to print an unallocated node.\n");
    }
  }
}

void printDict(dict_t *d) {
  if (d) {
    printNode(d->root, d->lang);
  } else {
    if (LOGGING) {
      printf("trying to print an unallocated dict.\n");
    }
  }
}