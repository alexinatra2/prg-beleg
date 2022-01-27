#include "dict.h"
#include "dictIO.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef BUF_SIZE
#define BUF_SIZE 128
#endif // !BUF_SIZE

dict_t *dict;

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <number>\n", argv[0]);
    return EXIT_FAILURE;
  }
  dict_t *dict = createDict(GERMAN);

  char *german = malloc(BUF_SIZE);
  char *english = malloc(BUF_SIZE);
  if (german && english) {

    for (int i = 0; i < atoi(argv[1]); i++) {
      printf("German word: ");
      fgets(german, BUF_SIZE, stdin);
      printf("English word: ");
      fgets(english, BUF_SIZE, stdin);
      insertEntryStr(dict, german, english);
    }
  }

  printDict(dict);

  deleteDict(dict);

  return EXIT_SUCCESS;
}