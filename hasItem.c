/*
 * Filename: hasItem.c
 * Author: Charles Li
 * Description: Checks if the player has the given item
 * Date: Jul 13 2017
 */

 #include "proj.h"

int hasItem( struct Player* player, int itemID ) {
  struct InvNode* currNode = player->itemInv;
  if(itemID < ITEM_ID_MIN) {
    currNode = player->potionInv;
  }
  if(itemID < POTION_ID_MIN) {
    currNode = player->armorInv;
  }
  if(itemID < ARMOR_ID_MIN) {
    currNode = player->weaponInv;
  }

  while(currNode != NULL) {
    if(currNode->item->id == itemID) {
      return 1;
    }

    currNode = currNode->next;
  }

  return 0;
}
