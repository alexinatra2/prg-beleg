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

void handleBaseDictNotPresent(char *program);
int handleBaseDictNull(dict_t *d, language_e lang);
int handleAdditionalDictCreation(int argc, char **argv);

dict_t *german_base_dict;
dict_t *german_additional_dict = NULL;
dict_t *english_base_dict;
dict_t *english_additional_dict = NULL;

int main(int argc, char **argv) {
  if (access(BASE_DICT_NAME, F_OK)) {
    handleBaseDictNotPresent(argv[0]);
  }

  german_base_dict = importDict(BASE_DICT_NAME, GERMAN);
  english_base_dict = importDict(BASE_DICT_NAME, ENGLISH);

  if (handleBaseDictNull(german_base_dict, GERMAN) ||
      handleBaseDictNull(english_base_dict, ENGLISH)) {
    fprintf(stderr, "A base dict is NULL\n");
    return EXIT_FAILURE;
  }

  if (handleAdditionalDictCreation(argc, argv)) {
    fprintf(
        stderr,
        "An error occurred while handling additional dictionary creation.\n");
    return EXIT_FAILURE;
  }

  mergeDicts(german_base_dict, german_additional_dict);
  mergeDicts(english_base_dict, english_additional_dict);

  printDict(german_base_dict);
  printDict(english_base_dict);

  exportDict(german_base_dict, BASE_DICT_NAME);

  deleteDict(german_base_dict);
  deleteDict(english_base_dict);

  return EXIT_SUCCESS;
}

void handleBaseDictNotPresent(char *program) {
  fprintf(stderr, "%s: file %s does not exist. Creating %s...\n", program,
          BASE_DICT_NAME, BASE_DICT_NAME);
  char *touch_file_command = malloc(strlen(BASE_DICT_NAME) + 8);
  if (touch_file_command) {
    sprintf(touch_file_command, "touch %s", BASE_DICT_NAME);
  }
  if (system(touch_file_command)) {
    fprintf(stderr, "Could not create file %s\n", BASE_DICT_NAME);
  }
  exit(EXIT_FAILURE);
}

int handleBaseDictNull(dict_t *d, language_e lang) {
  if (d) {
    return 0;
  }
  fprintf(stderr, "%s dict is NULL\n", lang == GERMAN ? "German" : "English");
  return 1;
}

int handleAdditionalDictCreation(int argc, char **argv) {
  if (argc < 2) {
    return 0;
  } else if (argc % 2) {
    german_additional_dict = createDict(GERMAN, "Additional words from cmd");
    english_additional_dict = createDict(ENGLISH, "Additional words from cmd");
    for (int i = 1; i < argc; i += 2) {
      insertEntryStr(german_additional_dict, argv[i], argv[i + 1]);
      insertEntryStr(english_additional_dict, argv[i], argv[i + 1]);
    }
    return !german_additional_dict || !english_additional_dict;
  } else if (access(argv[1], F_OK)) {
    german_additional_dict = importDict(argv[1], GERMAN);
    english_additional_dict = importDict(argv[1], ENGLISH);
    return !german_additional_dict || !english_additional_dict;
  }
  return 1;
}