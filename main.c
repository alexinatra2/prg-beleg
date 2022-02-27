#include "cgi.h"
#include "library.h"
#include "libraryio.h"
#include "medium.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

#define BASE_FILE_NAME "lib.csv"

void handleInserting();
void handleRemoving();
void handleLending();
void handleSearching();
void handleChangingOrder();
void handleQuitting();

lib_t *medium_type_lib;
lib_t *title_lib;
lib_t *artist_lib;
lib_t *borrower_lib;
lib_t *current;
char command_switch[32];
char medium_type_buffer[32];
char title_buffer[32];
char artist_buffer[32];
char borrower_buffer[32];

int main() {
  medium_type_lib = importLib(BASE_FILE_NAME, MEDIUM_TYPE);
  title_lib = importLib(BASE_FILE_NAME, TITLE);
  artist_lib = importLib(BASE_FILE_NAME, ARTIST);
  borrower_lib = importLib(BASE_FILE_NAME, BORROWER);
  current = medium_type_lib;
  printf("(i)nsert | (r)emove | (l)end/return back | (s)earch | (c)hange "
         "sorting order | (q)uit:\n");
  while (fgets(command_switch, 32, stdin) && command_switch[0] != 'q') {
    switch (command_switch[0]) {
    case 'i':
      handleInserting();
      break;
    case 'r':
      handleRemoving();
      break;
    case 'l':
      handleLending();
      break;
    case 's':
      handleSearching();
      printf("(i)nsert | (r)emove | (l)end/return back | (s)earch | (c)hange "
             "sorting order | (q)uit:\n");
      continue;
    case 'c':
      handleChangingOrder();
      break;
    default:
      break;
    }
    printf("%s\n\n", libToString(current));
    printf("(i)nsert | (r)emove | (l)end/return back | (s)earch | (c)hange "
           "sorting order | (q)uit:\n");
  }
  handleQuitting();
  return 0;
}

void handleInserting() {
  printf("input medium type (c - CD / d - DVD / b - book): \n");
  fgets(medium_type_buffer, 32, stdin);
  medium_type_e medium_type;
  switch (medium_type_buffer[0]) {
  case 'c':
    medium_type = CD;
    break;
  case 'd':
    medium_type = DVD;
    break;
  default:
    medium_type = BOOK;
    break;
  }
  printf("input title: \n");
  fgets(title_buffer, 32, stdin);
  printf("input artist: \n");
  fgets(artist_buffer, 32, stdin);
  medium_t *new_medium = createMedium(medium_type, title_buffer, artist_buffer);
  insertMedium(medium_type_lib, new_medium) &&
      insertMedium(title_lib, new_medium) &&
      insertMedium(artist_lib, new_medium) &&
      insertMedium(borrower_lib, new_medium);
}

void handleRemoving() {
  printf("input index to remove from the library:\n");
  fgets(command_switch, 32, stdin);
  int index = atoi(command_switch);
  removeMedium(medium_type_lib, index) && removeMedium(title_lib, index) &&
      removeMedium(artist_lib, index) && removeMedium(borrower_lib, index);
}

void handleLending() {
  printf("input index of the medium to lend to somebody:\n");
  fgets(command_switch, 32, stdin);
  int index = atoi(command_switch);
  printf("input the name of the person to lend the medium to or blank to "
         "return the medium:\n");
  fgets(borrower_buffer, 32, stdin);
  lend(medium_type_lib, index, borrower_buffer) &&
      lend(title_lib, index, borrower_buffer) &&
      lend(artist_lib, index, borrower_buffer) &&
      lend(borrower_lib, index, borrower_buffer);
}

void handleChangingOrder() {
  printf("(m)edium type | (b)orrower | (t)itle | (a)rtist:\n");
  fgets(command_switch, 32, stdin);
  switch (command_switch[0]) {
  case 'b':
    current = borrower_lib;
    break;
  case 't':
    current = title_lib;
    break;
  case 'a':
    current = artist_lib;
    break;
  default:
    current = medium_type_lib;
  }
}

void handleSearching() {
  printf("Enter the term to search for, if this is ordering by medium type, "
         "type (b - book | c - cd | d - dvd): \n");
  fgets(command_switch, 32, stdin);
  printf("%s\n", libToString(lookup(current, command_switch)));
}

void handleQuitting() { exportLib(medium_type_lib, BASE_FILE_NAME); }