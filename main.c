/*
 * Filename: main.c
 * Author: Charles Li
 * Description: Game start, initliazes player stats and plays the intro sequence
 * Date: June 27, 2017
 */

#include "proj.h"
#include "projStrings.h"
#include "projItems.h"

int main() {
  char* inputResult;
  char* nlPtr;
  char input[MAX_INPUT_LENGTH];
  struct Player player;
  player.maxHealth = START_HEALTH;
  player.currHealth = START_HEALTH;
  player.baseAtk = START_ATK;
  player.baseDef = START_DEF;
  player.currDef = player.baseDef;
  player.baseSpd = START_SPD;
  player.currSpd = player.baseSpd;
  player.money = 0;
  player.maxInvSize = DEF_INV_SIZE;
  player.currInvSize = 0;
  player.weaponInv = NULL;
  player.weaponInvNum = 0;
  player.armorInv = NULL;
  player.armorInvNum = 0;
  player.potionInv = NULL;
  player.potionInvNum = 0;
  player.itemInv = NULL;
  player.itemInvNum = 0;

  printf("-i. Oi. I see bodies dumped here all the time but this is the first \
          time one of them was breathing.\n");
  Sleep(1);
  printf("\nMy name's Maurice. What's yours?\n");

  do { //check for invalid name input
    inputResult = fgets(input, MAX_INPUT_LENGTH, stdin);
    if( inputResult == NULL ) { //respond about invalid input
      printf("\nNo it's not. What's your real name?\n");
    }
  } while(inputResult == NULL); //loop back up if input is invalid

  nlPtr = strchr(input, NEWLINE_CHAR); //check for name being too long
  if(nlPtr == NULL) { //newline char not found, name is at least 15 chars
    player.name[NAME_LENGTH - 1] = NULL_CHAR; //make sure name is terminated
    strncpy(player.name, input, MAX_INPUT_LENGTH); //copy first 15 chars
    printf("\nSo %s for short.\n", player.name); //respond to long name
  }
  else { //newline char found, input at most 14 chars, copy directly into name
    *nlPtr = NULL_CHAR; //terminate input
    strcpy(player.name, input); //copy input into name
  }

  Sleep(1);

  printf("\nWell %s, you can start by filling in the hole I dug for you.\n",
      player.name);
  printf(ADD_TO_INV_STR, SHOVEL_NAME);
  (void) addItem(&player, SHOVEL_SIZE, SHOVEL_NAME, SHOVEL_TYPE, SHOVEL_ATK, 
      SHOVEL_PRICE, SHOVEL_ID);
  Sleep(1);
  printf("\nAfter that, you'll probably want to go to the nearby town's \
          tavern and get yourself situated.\n");
  Sleep(1);
  printf("\nGood luck, and don't let me find you passed out on my grounds again.");

  Sleep(3);

  do {
    merriko(&player); //merriko always called first
  } while( toTellerian(&player) ); //recall merriko if player decides to return
}
