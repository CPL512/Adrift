/*
 * Filename: printInv.c
 * Author: Charles Li
 * Description: Prints out all of the player's inventory contents
 * Date: Jul 10 2017
 */

#include "proj.h"
#include "projStrings.h"

void printInv( struct Player* player, enum itemType type ) {
  struct InvNode* currNode;
  if(type == WEAPON_TYPE) {
    currNode = player->weaponInv;
  }
  else if(type == ARMOR_TYPE) {
    currNode = player->armorInv;
  }
  else if(type == POTION_TYPE) {
    currNode = player->potionInv;
  }
  else if(type == ITEM_TYPE) {
    currNode = player->itemInv;
  }
  else {
    printf("\nprintInv() received invalid enum itemType\n");
    return;
  }
  int i = 1;

  while(currNode != NULL) {
    printf("%i. %s %i %i %i\n", i, currNode->item->name, currNode->item->size,
        currNode->item->atk, currNode->item->price);
    currNode = currNode->next;
    i++;
  }
}
