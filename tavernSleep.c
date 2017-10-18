/*
 * Filename: tavernSleep.c
 * Author: Charles Li
 * Description: Heals the player up while resting in a tavern
 * Date: June 30, 2017
 */

#include "proj.h"

void tavernSleep( struct Player* player ) {
  player->currHealth = player->maxHealth;
  printf("\n* Health restored to full *\n");
}
