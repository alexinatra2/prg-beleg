#include "dict.h"
#include "dictIO.h"
#include <stdlib.h>

int main(int argc, char **argv) {
  dict_t *dict1 = createDict(GERMAN);
  insertEntryStr(dict1, "bauernhof", "farm") &&
      insertEntryStr(dict1, "ritter", "knight") &&
      insertEntryStr(dict1, "nacht", "night") &&
      insertEntryStr(dict1, "tag", "day") &&
      insertEntryStr(dict1, "jahr", "year");
  printDict(dict1);
  deleteDict(dict1);
  importDict("makefile", GERMAN);
  return 0;
}