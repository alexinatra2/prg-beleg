// TODO refactor
// TODO document
#include "dict.h"
#include "dictIO.h"
#include "entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef CONSTANTS
#define CONSTANTS
#define BASE_DICT_NAME "dict.csv"
#define BUF_SIZE 128
#endif // !CONSTANTS

void handleBaseDictNotPresent(char *program);
int handleBaseDictNull(dict_t *d, language_e lang);
int handleAdditionalDictCreation(int argc, char **argv);
int handleUserInput(char input);

dict_t *german_base_dict;
dict_t *english_base_dict;
dict_t *german_additional_dict = NULL;
dict_t *english_additional_dict = NULL;
int german_mode = 1;
char ger_buffer[BUF_SIZE];
char eng_buffer[BUF_SIZE];

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

  char buffer[BUF_SIZE];
  do {
    german_mode ? printDict(german_base_dict) : printDict(english_base_dict);
    printf("\nType one of the following commands:\n"
           "i - insert a new entry into the dictionary\n"
           "r - remove an entry from the dictionary\n"
           "s - switch from German to English view and vice versa\n"
           "l - lookup a word from the current language and get all its "
           "translations\n"
           "q - quit the program\n"
           "none of the above - reprint the previously shown dictionary\n");
    fgets(buffer, BUF_SIZE, stdin);
  } while (handleUserInput(buffer[0]));

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

// TODO validate input
int handleUserInput(char input) {
  switch (input) {
  case 'q':
    return 0;
  case 'i':
    printf("German word: ");
    fgets(ger_buffer, BUF_SIZE, stdin);
    printf("English word: ");
    fgets(eng_buffer, BUF_SIZE, stdin);
    insertEntryStr(german_base_dict, ger_buffer, eng_buffer) &&
        insertEntryStr(english_base_dict, ger_buffer, eng_buffer);
    return 1;
  case 'r':
    printf("German word: ");
    fgets(ger_buffer, BUF_SIZE, stdin);
    printf("English word: ");
    fgets(eng_buffer, BUF_SIZE, stdin);
    removeEntryStr(german_base_dict, ger_buffer, eng_buffer) &&
        removeEntryStr(english_base_dict, ger_buffer, eng_buffer);
    return 1;
  case 's':
    german_mode = german_mode ? 0 : 1;
    return 1;
  case 'l':
    printf("%s word: ", german_mode ? "German" : "English");
    fgets(ger_buffer, BUF_SIZE, stdin);
    dict_t *lookup_results =
        lookup(german_mode ? german_base_dict : english_base_dict, ger_buffer);
    printDict(lookup_results);
    deleteDict(lookup_results);
    return 1;
  default:
    return 1;
  }
}