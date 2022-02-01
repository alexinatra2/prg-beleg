#include "dict.h"
#include "dictIO.h"
#include "entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BASE_DICT_NAME
#define BASE_DICT_NAME "dict.csv"
#endif // !BASE_DICT_NAME

#ifndef CONSTANTS
#define CONSTANTS
#define OK 0
#define FAIL 1
#define BUF_SIZE 128
#endif // !CONSTANTS

int main(int argc, char **argv) {
  dict_t *german_base_dict;
  dict_t *german_additional_dict;
  dict_t *english_base_dict;
  dict_t *english_additional_dict;

  if (access(BASE_DICT_NAME, F_OK)) {
    fprintf(stderr, "%s: file %s does not exist. Creating %s...\n", argv[0],
            BASE_DICT_NAME, BASE_DICT_NAME);
    char *touch_file_command = malloc(strlen(BASE_DICT_NAME) + 8);
    if (touch_file_command) {
      sprintf(touch_file_command, "touch %s", BASE_DICT_NAME);
    }
    if (system(touch_file_command)) {
      fprintf(stderr, "Could not create file %s\n", BASE_DICT_NAME);
    }
    return EXIT_FAILURE;
  }

  german_base_dict = importDict(BASE_DICT_NAME, GERMAN);
  english_base_dict = importDict(BASE_DICT_NAME, ENGLISH);

  printDict(german_base_dict);
  printDict(english_base_dict);

  exportDict(german_base_dict, BASE_DICT_NAME);

  deleteDict(german_base_dict);
  deleteDict(english_base_dict);

  return EXIT_SUCCESS;
}