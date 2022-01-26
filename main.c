#include "dict.h"
#include "entry.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  dict_t *dict1 = createDict(GERMAN);
  printf("%d\n", insertEntryStr(dict1, "bauernhof", "farm") &&
                     insertEntryStr(dict1, "ritter", "knight") &&
                     insertEntryStr(dict1, "nacht", "night") &&
                     insertEntryStr(dict1, "tag", "day") &&
                     insertEntryStr(dict1, "jahr", "year"));

  printDict(dict1);

  dict_t *dict2 = createDict(GERMAN);
  printf("%d\n", insertEntryStr(dict2, "hallo", "hello") &&
                     insertEntryStr(dict2, "welt", "world") &&
                     insertEntryStr(dict2, "mann", "man") &&
                     insertEntryStr(dict2, "frau", "woman") &&
                     insertEntryStr(dict2, "kind", "child"));

  printDict(dict2);

  mergeDicts(dict1, dict2);
  printDict(dict1);

  deleteDict(dict2);
  return 0;
}