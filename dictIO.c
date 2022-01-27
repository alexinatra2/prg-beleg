#include "dictIO.h"
#include "dict.h"
#include "entry.h"
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
#define CSV_LINE_PATTERN                                                       \
  "^[:blank:]*[:alnum:]+[:blank:]*[,; ][:blank:]*[:alnum:]+[:blank:]*[,; "     \
  "]?[:blank:]*$"
#endif // !CSV_LINE_PATTERN

dict_t *importDict(char *file_name, language_e lang) {
  FILE *file = fopen(file_name, "r");
  if (!file) {
    return NULL;
  }
  char buffer[BUF_SIZE];
  dict_t *dict = createDict(lang);
  regex_t regex;
  int ret = regcomp(&regex, CSV_LINE_PATTERN, REG_EXTENDED);
  printf("%d\n", REG_NOMATCH == regexec(&regex, " a ; asdfsadf", 0, NULL, 0));
  return NULL;
  if (dict) {
    while (fgets(buffer, BUF_SIZE, file)) {
      if (regexec(&regex, buffer, 0, NULL, 0)) {
        return NULL;
      }
      char *first = strtok(buffer, TOKENS);
      char *second = strtok(NULL, TOKENS);
    }
  }
  fclose(file);
  regfree(&regex);
  return dict;
}

int exportDict(dict_t *d) { return 0; }