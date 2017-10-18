/*
 * Filename: readInLong.c
 * Author: Charles Li
 * Description: Reads stdin for user input and converts it to a long
 * Date: Jun 30 2017
 */

#include <errno.h>
#include "proj.h"

long readInLong() {
  char input[MAX_INPUT_LENGTH];
  long toReturn;
  char* endPtr;

  if(fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
    return -1;
  }
  errno = 0;
  toReturn = strtol(input, &endPtr, BASE);
  if(errno || input + 1 != endPtr || *endPtr != NEWLINE_CHAR) {
    return -1;
  }
  return toReturn;
}
