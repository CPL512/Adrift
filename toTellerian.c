/*
 * Filename: toTellerian.c
 * Author: Charles Li
 * Description: Conducts the sequence of battles between Merriko and Tellerian
 * Date: Jul 17 2017
 */

static void init();

#include "proj.h"
#include "projStrings.h"
#include "projItems.h"
#include "projEnemies.h"

#define NUM_ENEMIES 5

static struct Enemy enemyList[NUM_ENEMIES];

/* return 1 for go back, return 0 for continue forward */
int toTellerian( struct Player* player ) {
  init();
	
  char yesNo;
  long choice;

  int i;
  for(i = 0; i < NUM_ENEMIES; i++) {
    while(1) {
      printf(TRAVEL_PROMPT);
      printf(TRAVEL_OPT_STR);
      choice = readInLong();
      
      if(choice == FORWARD) {
        break;
      }
      else if(choice == INV) {
        while(1) {
          printf(CHECK_INV_PROMPT);
          printf(CHECK_INV_STR);
          choice = readInLong();

          if(choice == BACK) {
            break;
          }
          else if(choice == WEAPON) {
            printInv(player, WEAPON_TYPE);
          }
          else if(choice == ARMOR) {
            printInv(player, ARMOR_TYPE);
          }
          else if(choice == POTION) {
            while(1) {
              printf(EXIT_OPT);
              printInv(player, POTION_TYPE);
              printf(CONFIRM_POT_PROMPT);
              yesNo = readYesNo();
              if(yesNo == 1) {
                printf(POTION_PROMPT); //prompt player for potion selection
                if(choice == 0) { //exit selected, break potion loop
                  break;
                }
                else if(choice < 0 || choice > player->potionInvNum) {
                  printf(INVALID_MSG); //invalid input
                  continue;
                }
                else { //valid potion selected
                  int oldHealth;
                  int i;
 
                  struct InvNode* currNode = player->potionInv; //beginning of potion list
                  for(i = 1; i <= player->potionInvNum; i++) { //go to choice
                    if(i == choice) { //choice reached
                      oldHealth = player->currHealth; //track old health
                      player->currHealth += currNode->item->atk; //heal
                      if(player->currHealth > player->maxHealth) {
                        player->currHealth = player->maxHealth; //capped at max
                      }
                      printf(POTION_HEAL_STR, player->currHealth - oldHealth);
                      removeItem(player, currNode->item->id); //remove from inv
                      break; //choice reached, stop iterating
                    }
              
                    currNode = currNode->next; //choice not yet reached
                  }
                }
              }
              else if(yesNo == 0) {
                break;
              }
              else {
                printf(INVALID_MSG);
              }
            }
          }
          else if(choice == ITEM) {
            printInv(player, ITEM_TYPE);
          }
          else {
            printf(INVALID_MSG);
          }
        }
      }
      else if(choice == RET) {
        return 1;
      }
      else {
        printf(INVALID_MSG);
      }
    }
    if( battle(player, &enemyList[i]) ) {
      if( adrift(player) ) {
        return 1;
      }
      else {
        enemyList[i].currHealth = enemyList[i].maxHealth;
        i--;
      }
    }
  }

  return 0;
}

static void init() {
	enemyList[0].name = SLIME_NAME;
	enemyList[0].maxHealth = SLIME_HEALTH;
	enemyList[0].currHealth = SLIME_HEALTH;
	enemyList[0].atk = SLIME_ATK;
	enemyList[0].def = SLIME_DEF;
	enemyList[0].spd = SLIME_SPD;
	enemyList[0].money = SLIME_VAZ;

	enemyList[1].name = ATK_SLIME_NAME;
	enemyList[1].maxHealth = ATK_SLIME_HEALTH;
	enemyList[1].currHealth = ATK_SLIME_HEALTH;
	enemyList[1].atk = ATK_SLIME_ATK;
	enemyList[1].def = ATK_SLIME_DEF;
	enemyList[1].spd = ATK_SLIME_SPD;
	enemyList[1].money = ATK_SLIME_VAZ;

	enemyList[2].name = DEF_SLIME_NAME;
	enemyList[2].maxHealth = DEF_SLIME_HEALTH;
	enemyList[2].currHealth = DEF_SLIME_HEALTH;
	enemyList[2].atk = DEF_SLIME_ATK;
	enemyList[2].def = DEF_SLIME_DEF;
	enemyList[2].spd = DEF_SLIME_SPD;
	enemyList[2].money = DEF_SLIME_VAZ;

	enemyList[3].name = SPD_SLIME_NAME;
	enemyList[3].maxHealth = SPD_SLIME_HEALTH;
	enemyList[3].currHealth = SPD_SLIME_HEALTH;
	enemyList[3].atk = SPD_SLIME_ATK;
	enemyList[3].def = SPD_SLIME_DEF;
	enemyList[3].spd = SPD_SLIME_SPD;
	enemyList[3].money = SPD_SLIME_VAZ;

	enemyList[4].name = BAL_SLIME_NAME;
	enemyList[4].maxHealth = BAL_SLIME_HEALTH;
	enemyList[4].currHealth = BAL_SLIME_HEALTH;
	enemyList[4].atk = BAL_SLIME_ATK;
	enemyList[4].def = BAL_SLIME_DEF;
	enemyList[4].spd = BAL_SLIME_SPD;
	enemyList[4].money = BAL_SLIME_VAZ;
}
