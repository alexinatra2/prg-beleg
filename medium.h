#ifndef MEDIUM_H
#define MEDIUM_H

typedef struct medium medium_t;

typedef enum { BOOK, CD, DVD } medium_type_e;
typedef enum { MEDIUM, BORROWER, ARTIST } filter_type_e;

medium_t *createMedium(medium_type_e medium_type, char *medium_title, char *artist);
int deleteMedium(medium_t *medium);

int lendMediumTo(medium_t *medium, char *borrower);

char *mediumToString(medium_t *medium);

medium_type_e mediumTypeOf(medium_t *medium);
char *titleOf(medium_t *medium);
char *borrowerOf(medium_t *medium);
char *artistOf(medium_t *medium);

#endif // !MEDIUM_H