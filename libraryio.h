/**
 * @file libraryio.h
 * @author Alexander Holzknecht (https://github.com/alexinatra2)
 * @brief the header defining io behaviour involving library persistence
 * @version 0.1
 * @date 2022-02-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef LIBRARYIO_H
#define LIBRARYIO_H
#include "library.h"
#include "medium.h"

/**
 * @brief create a lib struct from a (csv-)file
 * 
 * @param file_name the file's name
 * @param filter_type the filter type of the resulting lib
 * @return lib_t* the imported lib
 */
lib_t *importLib(char *file_name, filter_type_e filter_type);

/**
 * @brief prints a lib struct's contents into a file
 * 
 * @param lib the lib
 * @param file_name the file's name
 * @return int whether the operation succeeded
 */
int exportLib(lib_t *lib, char *file_name);

#endif // !LIBRARYIO_H