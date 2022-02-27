#include "cgi.h"
#include "library.h"
#include "medium.h"
#include <stdio.h>
#include <stdlib.h>

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
  medium_type_lib = createLib(MEDIUM_TYPE);
  title_lib = createLib(TITLE);
  artist_lib = createLib(ARTIST);
  borrower_lib = createLib(BORROWER);
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
      break;
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
  removeMedium(medium_type_lib, new_medium) &&
      removeMedium(title_lib, new_medium) &&
      removeMedium(artist_lib, new_medium) &&
      removeMedium(borrower_lib, new_medium);
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

void handleSearching() {}

void handleLending() {}