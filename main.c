#include "medium.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  medium_t *medium = createMedium(BOOK, "bible", NULL);
  printf("%s\n", mediumToString(medium));
  return 0;
}