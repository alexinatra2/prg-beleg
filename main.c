#include "cgi.h"
#include "library.h"
#include "medium.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  lib_t *medium_type_lib = createLib(MEDIUM_TYPE);
  lib_t *title_lib = createLib(TITLE);
  lib_t *artist_lib = createLib(ARTIST);
  lib_t *borrower_lib = createLib(BORROWER);
  char command_switch[32];
  char medium_type_buffer[32];
  char title_buffer[32];
  char artist_buffer[32];
  char borrower_buffer[32];
  lib_t *current = medium_type_lib;
  printf("(i)nsert | (r)emove | (l)end/return back | (s)earch | (c)hange "
         "sorting order | (q)uit:\n");
  while (fgets(command_switch, 32, stdin) && command_switch[0] != 'q') {
    switch (command_switch[0]) {
    case 'i': {
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
      medium_t *new_medium =
          createMedium(medium_type, title_buffer, artist_buffer);
      insertMedium(medium_type_lib, new_medium) &&
          insertMedium(title_lib, new_medium) &&
          insertMedium(artist_lib, new_medium) &&
          insertMedium(borrower_lib, new_medium);
      break;
    }
    case 'r':
      break;
    case 's':
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
