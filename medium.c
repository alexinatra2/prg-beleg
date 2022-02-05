#include "medium.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOK_STR "book"
#define DVD_STR "dvd"
#define CD_STR "cd"
#define NO_TITLE_STR "no title"
#define UNKNOWN_ARTIST_STR "unknown"
#define NO_BORROWER_STR "nobody"

typedef struct medium {
  medium_type_e medium_type;
  char *title;
  char *artist;
  char *borrower;
} medium_t;

medium_t *createMedium(medium_type_e medium_type, char *medium_title,
                       char *artist) {
  medium_t *new_medium = malloc(sizeof(medium_t));
  if (!new_medium) {
    return NULL;
  }
  new_medium->medium_type = medium_type;
  new_medium->title = malloc(strlen(medium_title) + 1);
  if (new_medium->title) {
    strcpy(new_medium->title, medium_title);
  }
  if (!artist || !strcmp(artist, "")) {
    new_medium->artist = malloc(strlen(UNKNOWN_ARTIST_STR) + 1);
    new_medium->artist = UNKNOWN_ARTIST_STR;
  } else {
    new_medium->artist = malloc(strlen(artist) + 1);
    if (new_medium->artist) {
      strcpy(new_medium->artist, artist);
    }
  }
  return new_medium;
}

int deleteMedium(medium_t *medium) {
  if (!medium) {
    return 0;
  }
  free(medium->title);
  free(medium->artist);
  free(medium->borrower);
  free(medium);
  return 1;
}

int lendMediumTo(medium_t *medium, char *borrower) {
  if (!medium || !borrower) {
    return 0;
  }
  medium->borrower = malloc(strlen(borrower) + 1);
  if (medium->borrower) {
    strcpy(medium->borrower, borrower);
  }
  return 1;
}

char *mediumTypeToString(medium_type_e medium_type) {
  switch (medium_type) {
  case BOOK:
    return BOOK_STR;
  case CD:
    return CD_STR;
  case DVD:
    return DVD_STR;
  }
}

char *mediumToString(medium_t *medium) {
  if (!medium) {
    return NULL;
  }
  char *medium_type_str = mediumTypeToString(medium->medium_type);
  char *title_str = titleOf(medium);
  char *artist_str = artistOf(medium);
  char *borrower_str = borrowerOf(medium);
  int medium_str_size = strlen(medium_type_str) + strlen(title_str) +
                        strlen(artist_str) + strlen(borrower_str) + 51;
  char *medium_str = malloc(medium_str_size);
  if (!medium_str) {
    return NULL;
  }
  sprintf(medium_str,
          "[ medium type: %s | title: %s | artist: %s | lent to: %s ]",
          medium_type_str, title_str, artist_str, borrower_str);
  return medium_str;
}

medium_type_e mediumTypeOf(medium_t *medium);
char *titleOf(medium_t *medium) {
  if (!medium) {
    return NULL;
  }
  return medium->title && strcmp(medium->title, "") ? medium->title
                                                    : NO_TITLE_STR;
}

char *borrowerOf(medium_t *medium) {
  if (!medium) {
    return NULL;
  }
  return medium->borrower && strcmp(medium->borrower, "") ? medium->borrower
                                                          : NO_BORROWER_STR;
}

char *artistOf(medium_t *medium) { return medium->artist; }