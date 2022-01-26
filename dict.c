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

void deleteOneNode(node_t *node) {
  if (node) {
    if (VERBOSE_LOGGING) {
      printf("deleting (%s)\n", entryToString(node->entry, NONE));
    }
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
      node_t *intermediate;
      while (d->current) {
        intermediate = d->current;
        comp = compareEntries(e, d->current->entry, d->lang);
        if (LOGGING) {
          logComparison(e, d->current->entry, comp, d->lang);
        }
        if (comp < 0) {
          if (!d->current->left) {
            d->current->left = node;
            return 1;
          }
          d->current = d->current->left;
        } else if (comp > 0) {
          if (!d->current->right) {
            d->current->right = node;
            return 1;
          }
          d->current = d->current->right;
        } else {
          if (LOGGING) {
            printf("entry already present (%s)\n", entryToString(e, d->lang));
          }
          return 0;
        }
      }
    }
  }
  return 0;
}

int replaceDirectionalSuccessor(dict_t *d, int direction) {
  if (d) {
    if (direction < 0) {
    } else {
    }
  }
  return 0;
}

int replaceRoot(dict_t *d) {
  if (d && d->root) {
    node_t *former_root = d->root;
    if (!d->root->right) {
      d->root = d->root->left;
    } else {
      d->root = d->root->right;
      node_t *former_left = d->root->left;
      d->root->left = former_root->left;
      if (d->root->right) {
        d->current = d->root->right;
        while (d->current->left) {
          d->current = d->current->left;
        }
        d->current->left = former_left;
      } else {
        if (!d->root->left) {
          d->root->left = former_left;
        } else {
          d->current = d->root->left;
          while (d->current->right) {
            d->current = d->current->right;
          }
          d->current->right = former_left;
        }
      }
    }
    deleteOneNode(former_root);
    return 1;
  }
  return 0;
}

int removeEntry(dict_t *d, entry_t *e) {
  if (d && e) {
    resetToRoot(d);
    int comp = compareEntries(e, d->current->entry, d->lang);
    if (!comp) {
      return replaceRoot(d);
    }
    int prev_comp;
    node_t *next_node;
    while (comp && d->current) {
      prev_comp = comp;
      next_node = (comp < 0) ? d->current->left : d->current->right;
      if (next_node) {
        comp = compareEntries(e, next_node->entry, d->lang);
        if (!comp) {
          return replaceDirectionalSuccessor(d, prev_comp);
        }
      }
      d->current = next_node;
    }
  }
  return 0;
}

int insertEntryStr(dict_t *d, char *g, char *e) {
  return insertEntry(d, createEntry(g, e));
}

int removeEntryStr(dict_t *d, char *g, char *e) {
  return removeEntry(d, createEntry(g, e));
}

int max(int x, int y) { return x < y ? y : x; }

int currentDepthOfNode(node_t *n) {
  return n ? max(currentDepthOfNode(n->left), currentDepthOfNode(n->right)) + 1
           : 0;
}

int currentDepth(dict_t *d) { return currentDepthOfNode(d->root); }

// --- prg1-beleg --- utility function for importing dictionaries into one
int insertNodes(dict_t *d, node_t *n) {
  return (!n->left || insertNodes(d, n->left)) && insertEntry(d, n->entry) &&
         (!n->right || insertNodes(d, n->right));
}

int mergeDicts(dict_t *d1, dict_t *d2) {
  return d1 && d2 ? insertNodes(d1, d2->root) : 0;
}

void printNode(node_t *n, language_e lang) {
  if (n && n->entry) {
    printNode(n->left, lang);
    printf("%s\n", entryToString(n->entry, lang));
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