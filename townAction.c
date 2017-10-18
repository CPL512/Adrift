/*
 * Filename: townAction.c
 * Author: Charles Li
 * Description: Prompts the player for a choice as to what to do, and loops
 *              until a valid choice is made.
 * Date: June 28, 2017
 */

#include "proj.h"
#include "projStrings.h"

long townAction() {
  char input[MAX_INPUT_LENGTH];
  long choice = -1;
  char* endPtr;

  while(choice == -1) {
    printf(TOWN_ACTIONS_PROMPT);
    printf(TOWN_ACTIONS_STR);
    choice = readInLong();
    if(choice != TAVERN && choice != SHOP && choice != TALK	&&
        choice != CONTINUE) {
      printf(INVALID_MSG);
      choice = -1;
    }
  }

  return choice;
}
