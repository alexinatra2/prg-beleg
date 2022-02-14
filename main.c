#include "medium.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  medium_t *medium1 = createMedium(BOOK, "bible", NULL);
  medium_t *medium2 = createMedium(CD, "the dark side of the moon", "pink floyd");
  medium_t *medium3 = createMedium(BOOK, "alphabet", NULL);
  lendMediumTo(medium1, "emil");
  lendMediumTo(medium2, "karl");
  printf("%s\n", mediumToString(medium1));
  printf("%s\n", mediumToString(medium2));
  
  printf("%d\n", compareOnMediumType(medium3, medium1));

  return 0;
}
