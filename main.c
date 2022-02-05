#include "medium.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  medium_t *medium = createMedium(BOOK, "bible", NULL);
  lendMediumTo(medium, "klaus");
  printf("%s\n", mediumToString(medium));

  lendMediumTo(medium, "emil");
  printf("%s\n", mediumToString(medium));
  return 0;
}