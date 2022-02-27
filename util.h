/**
 * @file util.h
 * @author Alexander Holzknecht (https://github.com/alexinatra2)
 * @brief header defining some utility functions used throughout the whole project
 * @version 0.1
 * @date 2022-02-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef UTIL_H
#define UTIL_H

/**
 * @brief trim leading and trailing whitespaces
 *
 * @param str the string
 * @return char* the whitespace trimmed strin
 * Note: the pointer returned by this can be freed with the same allocator
 *  as the original string
 */
char *trim(char *str);

/**
 * @brief a case insensitive version of strcmp
 *
 * @param first the first string
 * @param second the second string
 * @return int 0 if the strings are equal in terms of the letters they use, not
 * regarding upper and lower case. Returns less than 0 if the first string is
 * alphabetically before the second and vice versa.
 */
int strcicmp(char const *first, char const *second);

#endif // !UTIL_H