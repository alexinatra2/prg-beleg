#include "dictIO.h"
#include "dict.h"
#include "entry.h"
#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 128
#endif // !BUF_SIZE

#ifndef TOKENS
#define TOKENS ",;"
#endif // !TOKENS

dict_t *importDict(char *file_name, language_e lang) {
  FILE *file = fopen(file_name, "r");
  if (!file) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  char *buffer = malloc(BUF_SIZE);
  char *description_str = malloc(strlen(file_name) + 26);
  sprintf(description_str, "Dictionary imported from %s", file_name);
  dict_t *dict = createDict(lang, description_str);
  if (dict) {
    while (!feof(file) && fgets(buffer, BUF_SIZE, file)) {
      if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = 0;
      }
      char *german = strtok(buffer, TOKENS);
      char *english = strtok(NULL, TOKENS);
      insertEntry(dict, createEntry(german, english));
    }
  }
  fclose(file);
  return dict;
}

// TODO change this to not use has next or improve has next
int exportDict(dict_t *d, char *file_name) {
  FILE *file = fopen(file_name, "w");
  if (!file) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  resetToRoot(d);
  while (currentExists(d)) {
    fprintf(file, "%s\n", entryToString(getCurrent(d)));
    iterateDict(d);
  }
  fclose(file);
  return 0;
}