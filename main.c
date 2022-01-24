#include "dict.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  entry_t *entry = createEntry("hallo", "hello");

  printf("%s\n", entryToString(entry, GERMAN));
  return 0;
}