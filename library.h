/**
 * @file library.h
 * @author Alexander Holzknecht (https://github.com/alexinatra2)
 * @brief the header defining behaviour for library structs
 * @version 0.1
 * @date 2022-02-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef LIBRARY_H
#define LIBRARY_H

#include "medium.h"

/**
 * @brief a struct representing libraries in form of an
 * aggregation of media
 * 
 */
typedef struct lib lib_t;

/**
 * @brief Create a lib struct with a filter type
 * 
 * @param filter_type the filter type
 * @return lib_t* a new lib reference
 */
lib_t *createLib(filter_type_e filter_type);

/**
 * @brief Delete a lib struct
 * 
 * @param lib the lib to delete
 * @return int whether the operation succeeded or not
 */
int deleteLib(lib_t *lib);

/**
 * @brief Insert a medium into a library. Does not insert if
 * the medium with the exact same data is already present.
 *
 * @param lib the lib
 * @param medium the medium to insert
 * @return int whether the operation succeeded or not. Fails if
 * the lib does not exist, the medium does not exist or the medium is
 * already present
 */
int insertMedium(lib_t *lib, medium_t *medium);

/**
 * @brief Set the borrower of a medium to the desired string
 * 
 * @param lib the lib
 * @param index the mediums index visible from the table
 * @param borrower the borrower string
 * @return int whether the operation was successful
 */
int lend(lib_t *lib, int index, char *borrower);

/**
 * @brief remove a medium from a lib
 * 
 * @param lib the lib
 * @param index the mediums index visible from the table
 * @return int whether the operation was successful
 */
int removeMedium(lib_t *lib, int index);

/**
 * @brief creates a lib containing only the media pertaining to
 * the search string
 * 
 * @param lib the original lib
 * @param search_string the string by which to filter
 * @return lib_t* the lib containing only the filtered elements 
 */
lib_t *lookup(lib_t *lib, char *search_string);

/**
 * @brief a utility function to reset the libs position to the start
 *
 * @param lib the lib
 * @return int whether the operation was successful. Only fails if the lib
 * does not exist
 */
int resetToRoot(lib_t *lib);

/**
 * @brief a utility function to iterate through the libs content. Performs
 * exactly one iteraton
 *
 * @param lib the lib
 * @return int whether the operation was successful. If the iteration results
 * in the new current element being NULL, this returns 0
 */
int iterate(lib_t *lib);

/**
 * @brief a utility function to get the current medium
 * 
 * @param lib the lib
 * @return medium_t* the current medium
 */
medium_t *currentMedium(lib_t *lib);

/**
 * @brief a to string function for lib structs
 * 
 * @param lib the lib
 * @return char* the string representation of a lib
 */
char *libToString(lib_t *lib);

#endif // !LIBRARY_H
