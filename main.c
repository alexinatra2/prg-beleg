#include "dict.h"
#include "dictIO.h"
#include "entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 128
#endif // !BUF_SIZE

#ifndef BASE_DICT_NAME
#define BASE_DICT_NAME "dict.csv"
#endif // !BASE_DICT_NAME

int main(int argc, char **argv) {
  dict_t *g = importDict(BASE_DICT_NAME, GERMAN);
  dict_t *e = importDict(BASE_DICT_NAME, ENGLISH);

  printDict(g);
  printDict(e);

  dict_t *t = lookup(g, argc > 1 ? argv[1] : "");
  printDict(t);

  exportDict(g, BASE_DICT_NAME);

  deleteDict(g);
  deleteDict(e);

  return EXIT_SUCCESS;
}