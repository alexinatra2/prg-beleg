/**
 * @file util.c
 * @author Alexander Holzknecht (https://github.com/alexinatra2)
 * @brief the c file implementing the declared behaviour of util.h
 * @version 0.1
 * @date 2022-02-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "util.h"
#include <ctype.h>
#include <string.h>

/**
 * @see
 * https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
 * comment by indiv answered Sep 23, 2008 at 18:48 and last edited Jul 26,
 * 2019 at 20:19 at the time of writing this
 */
char *trim(char *str) {
  size_t len = 0;
  char *frontp = str;
  char *endp = NULL;

  if (str == NULL) {
    return NULL;
  }
  if (str[0] == '\0') {
    return str;
  }

  len = strlen(str);
  endp = str + len;
  while (isspace((unsigned char)*frontp)) {
    ++frontp;
  }
  if (endp != frontp) {
    while (isspace((unsigned char)*(--endp)) && endp != frontp) {
    }
  }

  if (frontp != str && endp == frontp)
    *str = '\0';
  else if (str + len - 1 != endp)
    *(endp + 1) = '\0';
  endp = str;
  if (frontp != str) {
    while (*frontp) {
      *endp++ = *frontp++;
    }
    *endp = '\0';
  }

  return str;
}

/**
 * @see
 * https://stackoverflow.com/questions/5820810/case-insensitive-string-comparison-in-c
 * comment by Zohar81 answered Jan 4, 2016 at 11:16
 */
int strcicmp(const char *s1, const char *s2) {
  const unsigned char *us1 = (const unsigned char *)s1;
  const unsigned char *us2 = (const unsigned char *)s2;

  while (tolower(*us1) == tolower(*us2++)) {
    if (*us1++ == '\0') {
      return 0;
    }
  }
  return tolower(*us1) - tolower(*--us2);
}