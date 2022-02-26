#include "cgi.h"
#include "library.h"
#include "medium.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  medium_t *medium1 = createMedium(BOOK, "bible", NULL);
  medium_t *medium2 =
      createMedium(CD, "the dark side of the moon", "pink floyd");
  medium_t *medium3 = createMedium(BOOK, "alphabet", NULL);
  lendMediumTo(medium1, "emil");
  lendMediumTo(medium2, "karl");

  printf("%d\n", compareOnMediumType(medium3, medium1));

  lib_t *lib = createLib(MEDIUM_TYPE);
  insertMedium(lib, medium1);
  insertMedium(lib, medium2);

  lib_t *lib1 = createLib(TITLE);
  insertMedium(lib1, medium1);
  insertMedium(lib1, medium2);

  lib_t *lib2 = createLib(ARTIST);
  insertMedium(lib2, medium1);
  insertMedium(lib2, medium2);

  lib_t *lib3 = createLib(BORROWER);
  insertMedium(lib3, medium1);
  insertMedium(lib3, medium2);

  printf("%s\n\n", libToString(lib));
  printf("%s\n\n", libToString(lib1));
  printf("%s\n\n", libToString(lib2));
  printf("%s\n\n", libToString(lib3));

  return 0;
}
