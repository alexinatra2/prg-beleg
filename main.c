#include "dict.h"
#include "entry.h"
#include <stdio.h>
#include <stdlib.h>

int LOGGING = 1;

int main(int argc, char **argv) {
  entry_t *entry1 = createEntry("hallo", "hello");
  entry_t *entry2 = createEntry("welt", "world");
  entry_t *entry3 = createEntry("erde", "earth");
  entry_t *entry4 = createEntry("umwelt", "environment");
  entry_t *entry5 = createEntry("wort", "word");

  dict_t *dict = createDict(GERMAN);

  insertEntry(dict, entry1);
  insertEntry(dict, entry2);
  insertEntry(dict, entry3);
  insertEntry(dict, entry4);
  insertEntry(dict, entry5);

  printDict(dict);

  deleteDict(dict);
  return 0;
}