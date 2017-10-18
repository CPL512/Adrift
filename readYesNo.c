/*
 * Filename: readYesNo.c
 * Author: Charles Li
 * Description: Reads user input for a yes or no
 * Date: Jul 05 2017
 */

#include "proj.h"

char readYesNo() {
  char input[MAX_INPUT_LENGTH];

  if(fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
    return (char) -1;
  }

  if(!stricmp(input, "y") || !stricmp(input, "yes")) {
    return (char) 1;
  }
  else if(!stricmp(input, "n") || !stricmp(input, "no")) {
    return (char) 0;
  }
  else {
    return (char) -1;
  }
}
