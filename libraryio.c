/**
 * @file libraryio.c
 * @author Alexander Holzknecht (https://github.com/alexinatra2)
 * @brief the c file implementing the declared behaviour of libraryio.h
 * @version 0.1
 * @date 2022-02-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "libraryio.h"
#include "library.h"
#include "medium.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LIBRARYIO_VARS
#define LIBRARYIO_VARS

#define BUF_SIZE 128
#define TOKENS "|,;"

#endif // !LIBRARYIO_VARS

lib_t *importLib(char *file_name, filter_type_e filter_type) {
  FILE *file = fopen(file_name, "r");
  if (!file) {
    return createLib(filter_type);
  }
  char *buffer = malloc(BUF_SIZE);
  char *description_str = malloc(strlen(file_name) + 23);
  sprintf(description_str, "Library imported from %s", file_name);
  lib_t *lib = createLib(filter_type);
  if (lib) {
    while (!feof(file) && fgets(buffer, BUF_SIZE, file)) {
      if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = 0;
      }
      char *medium_type_string = strtok(buffer, TOKENS);
      char *medium_title = strtok(NULL, TOKENS);
      char *medium_artist = strtok(NULL, TOKENS);
      char *medium_borrower = trim(strtok(NULL, TOKENS));
      medium_t *medium = createMedium(stringToMediumType(medium_type_string),
                                      medium_title, medium_artist);
      if (strcmp(medium_borrower, "-") != 0) {
        lendMediumTo(medium, medium_borrower);
      }
      insertMedium(lib, medium);
    }
  }
  fclose(file);
  return lib;
}

int exportLib(lib_t *lib, char *file_name) {
  FILE *file = fopen(file_name, "w");
  resetToRoot(lib);
  while (currentMedium(lib)) {
    fprintf(file, "%s\n", mediumToCSVString(currentMedium(lib)));
    iterate(lib);
  }
  fclose(file);
  return 0;
}