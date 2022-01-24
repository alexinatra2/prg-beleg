#include "dict.h"
#include "entry.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>

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
    if (VERBOSE_LOGGING) {
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

void resetToRoot(dict_t *d) { d->current = d->root; }

void traverseLeft(dict_t *d) { d->current = d->current->left; }

void traverseRight(dict_t *d) { d->current = d->current->right; }

void logComparison(entry_t *entry1, entry_t *entry2, int comp,
                   language_e lang) {
  char *entry1_str = entryToString(entry1, lang);
  char *entry2_str = entryToString(entry2, lang);
  if (comp < 0) {
    LOG_YELLOW("{");
    LOG_YELLOW(entry1_str);
    LOG_YELLOW("} < {");
    LOG_YELLOW(entry2_str);
    LOG_YELLOW("}\n");
  } else if (comp > 0) {
    LOG_RED("{");
    LOG_RED(entry1_str);
    LOG_RED("} > {");
    LOG_RED(entry2_str);
    LOG_RED("}\n");
  } else {
    LOG("{");
    LOG(entry1_str);
    LOG("} = {");
    LOG(entry2_str);
    LOG("}\n");
  }
}

int insertEntry(dict_t *d, entry_t *e) {
  if (d) {
    node_t *node = createNode(e);
    if (node) {
      if (!d->root) {
        d->root = node;
        return 1;
      }
      resetToRoot(d);
      int comp;
      while (d->current) {
        comp = compareEntries(e, d->current->entry, d->lang);
        if (LOGGING) {
          logComparison(e, d->current->entry, comp, d->lang);
        }
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
  printf("\n--- %s - %s ---\n", d->lang == GERMAN ? "GERMAN" : "ENGLISH",
         d->lang == ENGLISH ? "GERMAN" : "ENGLISH");
  if (d) {
    printNode(d->root, d->lang);
  }
  printf("------------------------\n\n");
}