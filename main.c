#include "dict.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  entry_t *entry = createEntry("hallo", "hello");

  dict_t *dict = createDict(GERMAN);
  deleteDict(dict);
  return 0;
}