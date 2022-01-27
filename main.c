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

int main(int argc, char **argv) {
  if (argc < 2 || argc > 3) {
    fprintf(stderr, "usage: %s <amount_of_dict_entries_to_insert> [ger|eng]\n",
            argv[0]);
    return EXIT_FAILURE;
  }

  language_e lang = argc == 3 && strcmp(argv[2], "eng") == 0 ? ENGLISH : GERMAN;

  dict_t *dict = createDict(lang);

  char first[BUF_SIZE];
  char second[BUF_SIZE];
  for (int i = 0; i < atoi(argv[1]); i++) {
    printf("%s word: ", lang == GERMAN ? "German" : "English");
    fgets(first, BUF_SIZE, stdin);
    printf("%s word: ", lang == ENGLISH ? "German" : "English");
    fgets(second, BUF_SIZE, stdin);
    lang == GERMAN ? insertEntryStr(dict, first, second)
                   : insertEntryStr(dict, second, first);
  }

  printDict(dict);

  return EXIT_SUCCESS;
}