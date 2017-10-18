/*
 * Filename: battle.c
 * Author: Charles Li
 * Description: Conducts battle between the player and a given enemy
 * Date: Jul 11 2017
 */

 #include "proj.h"
 #include "projStrings.h"

static int playerTurn( struct Player* player, struct Enemy* enemy );
static int enemyTurn( struct Player* player, struct Enemy* enemy );

static struct Item* atkWeapon;

int battle( struct Player* player, struct Enemy* enemy ) {
  struct InvNode* currNode;
  long choice = 0;
  char attacked;
  char guarded;
  char potioned;

  while(1) { //battle loop
    atkWeapon = NULL;
    attacked = 0;
    guarded = 0;
    potioned = 0;

    while(1) { //prompt loop
      printf(BATTLE_PROMPT);
      printf(BATTLE_OPT_STR);
      choice = readInLong();

      if(choice == ATTACK) { //attack selected
        while(1) {
          printf(EXIT_OPT); //print exit option and weapon list
          printInv(player, WEAPON_TYPE);
          printf(WEAPON_PROMPT); //prompt player for weapon selection
          if(choice == 0) { //exit selected, break weapon loop and reprompt
           break;
          }
          else if(choice < 0 || choice > player->weaponInvNum) {
            printf(INVALID_MSG); //invalid input
            continue;
          }
          else { //valid weapon selected
            int i;

            currNode = player->weaponInv; //begin at beginning of weapon list
            for(i = 1; i <= player->weaponInvNum; i++) { //iterate to choice
              if(i == choice) { //choice reached
                atkWeapon = currNode->item; //set weapon of choice
                attacked = 1;
                break; //break iteration loop
              }
              
              currNode = currNode->next; //choice not yet reached, keep going
            }
            break; //break weapon choice loop
          }
        }
        if(attacked) { //break if weapon chosen, don't if exit option chosen
          break;
        }
      }
      else if(choice == GUARD) { //guard selected
        guarded = 1; //set variable and break loop
        break;
      }
      else if(choice == POTION) { //use potion selected
        while(1) {
          printf(EXIT_OPT); //print exit option and potion list
          printInv(player, POTION_TYPE);
          printf(POTION_PROMPT); //prompt player for potion selection
          if(choice == 0) { //exit selected, break potion loop and reprompt
           break;
          }
          else if(choice < 0 || choice > player->potionInvNum) {
            printf(INVALID_MSG); //invalid input
            continue;
          }
          else { //valid potion selected
            int oldHealth;
            int i;

            currNode = player->potionInv; //begin at beginning of potion list
            for(i = 1; i <= player->potionInvNum; i++) { //iterate to choice
              if(i == choice) { //choice reached
                oldHealth = player->currHealth; //track old health
                player->currHealth += currNode->item->atk; //heal by potion atk
                if(player->currHealth > player->maxHealth) {
                  player->currHealth = player->maxHealth; //capped at max
                }
                printf(POTION_HEAL_STR, player->currHealth - oldHealth);
                removeItem(player, currNode->item->id); //remove pot from inv
                potioned = 1; //used potion is true so skip player turn
                break; //choice reached, stop iterating
              }
              
              currNode = currNode->next; //choice not yet reached, keep going
            }
            break; //potion used, stop prompting for potion choice
          }
        }
        if(potioned) { //break if potion used, don't if exit option chosen
          break;
        }
      }
      else {
        printf(INVALID_MSG);
      }
    }

    if(player->currSpd >= enemy->spd) { //player faster, goes first
      if(atkWeapon != NULL) { //conduct player turn only if attack weapon set
        if(playerTurn(player, enemy)) { //returns 1 on enemy defeat
          printf(DEFEAT_STR, enemy->name);
          printf(ENEMY_DROPPED_VAZ, enemy->name, enemy->money);
          player->money += enemy->money;
          return 0; //return player not defeated
        }
      }
      if(enemyTurn(player, enemy)) { //returns 1 if player defeated
        printf(DEFEAT_STR, PLAYER_STR);
        return 1; //return player defeated
      }
    }
    else { //enemy faster, goes first
      if(enemyTurn(player, enemy)) { //returns 1 if player defeated
        printf(DEFEAT_STR, PLAYER_STR);
        return 1; //return player defeated
      }
      if(atkWeapon != NULL) { //conduct player turn only if attack weapon set
        if(playerTurn(player, enemy)){ //returns 1 on enemy defeat
          printf(DEFEAT_STR, enemy->name);
          printf(ENEMY_DROPPED_VAZ, enemy->name, enemy->money);
          player->money += enemy->money;
          return 0; //return player not defeated
        }
      }
    }
  }
}

static int playerTurn( struct Player* player, struct Enemy* enemy ) {
  int hitChance = (double)player->currSpd / enemy->spd * HIT_CHANCE_FACTOR;
  hitChance = hitChance + HIT_CHANCE_MIN; //calculate chance of hitting
  int hitRoll = (rand() % HIT_CHANCE_MAX) + 1; //roll to see if attack hits
  int dmg = player->baseAtk + atkWeapon->atk - enemy->def; //calculate damage
  if(dmg < 0) { //not using max() because of portability problems
    dmg = 0; //damage cannot be negative
  }

  printf(ATK_STR, atkWeapon->name);

  if(hitRoll <= hitChance) { //attack hits
    printf(DAMAGE_STR, enemy->name, dmg);
    enemy->currHealth -= dmg;
  }
  else { //attack misses
    printf(MISSED_STR);
  }

  if(enemy->currHealth <= 0) {
    return 1; //return enemy defeated
  }

  return 0; //return enemy not defeated
}

static int enemyTurn( struct Player* player, struct Enemy* enemy ) {
  int hitChance = (double)enemy->spd / player->currSpd * HIT_CHANCE_FACTOR;
  hitChance = hitChance + HIT_CHANCE_MIN; //calculate chance of hitting
  int hitRoll = (rand() % HIT_CHANCE_MAX) + 1; //roll to see if attack hits
  int dmg = enemy->atk - player->currDef; //calculate damage
  if(dmg < 0) { //not using max() because of portability problems
    dmg = 0; //damage cannot be negative
  }

  printf(ENEMY_STR, enemy->name);
  if(hitRoll <= hitChance) { //attack hits
    printf(DAMAGE_STR, PLAYER_STR, dmg);
    player->currHealth -= dmg;
  }
  else { //attack misses
    printf(MISSED_STR);
  }

  if(player->currHealth <= 0) {
    return 1; //return player defeated
  }

  return 0; //return player not defeated
}
