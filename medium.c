#include "medium.h"
#include "util.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOK_STR "book"
#define DVD_STR "dvd"
#define CD_STR "cd"
#define NO_TITLE_STR "no title"
#define UNKNOWN_ARTIST_STR "unknown"
#define NO_BORROWER_STR "-"

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
  char *trimmed_title = trim(medium_title);
  if (!medium_title || !strcmp(trimmed_title, "")) {
    new_medium->title = malloc(strlen(NO_TITLE_STR) + 1);
    strcpy(new_medium->title, NO_TITLE_STR);
  } else {
    new_medium->title = malloc(strlen(trimmed_title) + 1);
    if (new_medium->title) {
      strcpy(new_medium->title, trimmed_title);
    }
  }
  char *trimmed_artist = trim(artist);
  if (!artist || !strcmp(trimmed_artist, "")) {
    new_medium->artist = malloc(strlen(UNKNOWN_ARTIST_STR) + 1);
    strcpy(new_medium->artist, UNKNOWN_ARTIST_STR);
  } else {
    new_medium->artist = malloc(strlen(trimmed_artist) + 1);
    if (new_medium->artist) {
      strcpy(new_medium->artist, trimmed_artist);
    }
  }
  new_medium->borrower = NO_BORROWER_STR;
  return new_medium;
}

medium_t *cloneMedium(medium_t *medium) {
  if (!medium) {
    return NULL;
  }
  medium_t *new_medium = malloc(sizeof(medium_t));
  if (!new_medium) {
    return NULL;
  }
  new_medium->medium_type = medium->medium_type;
  new_medium->title = malloc(strlen(medium->title) + 1);
  if (new_medium->title) {
    strcpy(new_medium->title, medium->title);
  }
  new_medium->artist = malloc(strlen(medium->artist) + 1);
  if (new_medium->artist) {
    strcpy(new_medium->artist, medium->artist);
  }
  new_medium->borrower = malloc(strlen(medium->borrower) + 1);
  if (new_medium->borrower) {
    strcpy(new_medium->borrower, medium->borrower);
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
  char *trimmed_borrower = trim(borrower);
  medium->borrower = malloc(strlen(trimmed_borrower) + 1);
  if (medium->borrower) {
    strcpy(medium->borrower, trimmed_borrower);
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
  char *medium_str = malloc(114);
  if (!medium_str) {
    return NULL;
  }
  sprintf(medium_str, "%-4s | %-32s | %-32s | %-32s",
          mediumTypeToString(medium->medium_type), titleOf(medium),
          artistOf(medium), borrowerOf(medium));
  return medium_str;
}

char *mediumToCSVString(medium_t *medium) {
  if (!medium) {
    return NULL;
  }
  char *medium_str = malloc(108);
  if (!medium_str) {
    return NULL;
  }
  sprintf(medium_str, "%s, %s, %s, %s", mediumTypeToString(medium->medium_type),
          titleOf(medium), artistOf(medium), borrowerOf(medium));
  return medium_str;
}

medium_type_e stringToMediumType(char *string) {
  if (!string) {
    return BOOK;
  }
  switch (string[0]) {
  case 'c':
    return CD;
  case 'd':
    return DVD;
  default:
    return BOOK;
  }
}

medium_type_e mediumTypeOf(medium_t *medium) {
  if (!medium) {
    return BOOK;
  }
  return medium->medium_type;
}

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

char *artistOf(medium_t *medium) {
  if (!medium) {
    return NULL;
  }
  return medium->artist;
}

int compareOnTitle(medium_t *medium1, medium_t *medium2) {
  if (!medium1 || !medium2) {
    return 0;
  }
  return strcicmp(medium1->title, medium2->title);
}

int compareOnMediumType(medium_t *medium1, medium_t *medium2) {
  if (!medium1 || !medium2) {
    return 0;
  }
  return medium1->medium_type == medium2->medium_type
             ? compareOnTitle(medium1, medium2)
             : medium1->medium_type < medium2->medium_type ? -1 : 1;
}

int compareOnBorrower(medium_t *medium1, medium_t *medium2) {
  if (!medium1 || !medium2) {
    return 0;
  }
  return strcicmp(medium1->borrower, medium2->borrower);
}

int compareOnArtist(medium_t *medium1, medium_t *medium2) {
  if (!medium1 || !medium2) {
    return 0;
  }
  return strcicmp(medium1->artist, medium2->artist);
}

int compareOn(medium_t *medium1, medium_t *medium2, filter_type_e filter_type) {
  switch (filter_type) {
  case MEDIUM_TYPE:
    return compareOnMediumType(medium1, medium2);
  case TITLE:
    return compareOnTitle(medium1, medium2);
  case BORROWER:
    return compareOnBorrower(medium1, medium2);
  case ARTIST:
    return compareOnArtist(medium1, medium2);
  }
}