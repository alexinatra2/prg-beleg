/**
 * @file medium.h
 * @author Alexander Holzknecht (https://github.com/alexinatra2)
 * @brief the header defining functionality for the medium struct
 * @version 0.1
 * @date 2022-02-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MEDIUM_H
#define MEDIUM_H

/**
 * @brief a struct representing a medium
 * 
 */
typedef struct medium medium_t;

/**
 * @brief an enum to differentiate media by its type
 * 
 */
typedef enum { BOOK, CD, DVD } medium_type_e;

/**
 * @brief an enum mostly used by the lib struct to be able to filter
 * by specific attributes
 * 
 */
typedef enum { MEDIUM_TYPE, TITLE, BORROWER, ARTIST } filter_type_e;

/**
 * @brief Create a reference to a medium
 * 
 * @param medium_type the type 
 * @param medium_title the title, if left blank "no title"
 * @param artist the artist, if left blank "unknown"
 * @return medium_t* a reference to a medium struct
 */
medium_t *createMedium(medium_type_e medium_type, char *medium_title,
                       char *artist);

/**
 * @brief Create a copy of a medium reference
 * 
 * @param medium the medium to be cloned
 * @return medium_t* a copy of the medium 
 */
medium_t *cloneMedium(medium_t *medium);

/**
 * @brief delete the contents of a medium and its reference
 * 
 * @param medium the medium to be deleted
 * @return int whether the operation succeeded (1) or not (0)
 */
int deleteMedium(medium_t *medium);

/**
 * @brief sets the borrower field of a medium to borrower
 *
 * @param medium the medium
 * @param borrower the borrower
 * @return int whether the operation was successful. This fails if either the
 * medium does not exist
 */
int lendMediumTo(medium_t *medium, char *borrower);

/**
 * @brief a to string function for medium
 * 
 * @param medium the medium
 * @return char* the string representation of the medium
 */
char *mediumToString(medium_t *medium);

/**
 * @brief a to string function for medium, for printing into csv files
 * 
 * @param medium the medium
 * @return char* the csv string to be printed to the file
 */
char *mediumToCSVString(medium_t *medium);

/**
 * @brief a conversion function of string to medium type
 *
 * @param string the string
 * @return medium_type_e the resulting media type. If the string
 * was blank this is set to BOOK
 */
medium_type_e stringToMediumType(char *string);

/**
 * @brief a getter function for medium type
 * 
 * @param medium the medium 
 * @return medium_type_e its medium typ
 */
medium_type_e mediumTypeOf(medium_t *medium);

/**
 * @brief a getter function for title
 * 
 * @param medium the medium
 * @return char* its title
 */
char *titleOf(medium_t *medium);

/**
 * @brief a getter function for borrower
 * 
 * @param medium the medium
 * @return char* the person currently borrowing the medium
 */
char *borrowerOf(medium_t *medium);

/**
 * @brief a getter function for artist
 * 
 * @param medium the medium
 * @return char* its artist
 */
char *artistOf(medium_t *medium);

/**
 * @brief a function for comparing media with each other
 *
 * @param medium1 the first medium
 * @param medium2 the second medium
 * @param filter_type the filter which to compare by
 * @return int 0 if the elements are equal. Less than 0 if the first medium is
 * considered before the second and vice versa.
 */
int compareOn(medium_t *medium1, medium_t *medium2, filter_type_e filter_type);

#endif // !MEDIUM_H