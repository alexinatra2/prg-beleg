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
#define TOKENS ",; "
#endif // !TOKENS

#ifndef CSV_LINE_PATTERN
#define CSV_LINE_PATTERN "^(\t )*[:alpha:]+(\t )*[\t ,;]?(\t )*[:alpha:]+(\t )$"
#endif // !CSV_LINE_PATTERN

dict_t *importDict(char *file_name, language_e lang) {
  FILE *file = fopen(file_name, "r");
  if (!file) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  char *buffer = malloc(BUF_SIZE);
  dict_t *dict = createDict(lang);
  regex_t *regex = malloc(sizeof(regex_t));
  regcomp(regex, CSV_LINE_PATTERN, REG_EXTENDED);
  if (dict) {
    while (!feof(file) && fgets(buffer, BUF_SIZE, file)) {
      //  regexec(regex, buffer, 0, NULL, 0) != _REG_NOMATCH) {
      if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = 0;
      }
      char *german = strtok(buffer, TOKENS);
      char *english = strtok(NULL, TOKENS);
      insertEntryStr(dict, german, english);
    }
  }
  fclose(file);
  // regfree(regex);
  return dict;
}

int exportDict(dict_t *d, char *file_name) {
  FILE *file = fopen(file_name, "w");
  if (!file) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return 0;
}