/*
 * Filename: removeItem.c
 * Author: Charles Li
 * Description: Removes an item from the player's inventory using its ID
 * Date: Jul 07 2017
 */

#include "proj.h"
#include "projStrings.h"

int removeItem( struct Player* player, int itemID ) {
  if( !hasItem(player, itemID) ) { //player doesn't have specified item
    return 0; //nothing removed, return
  }

  struct InvNode** invPtr = &player->itemInv; //points to an inv list
  char* invNumPtr = &player->itemInvNum; //points to size of inv list
  if(itemID < ITEM_ID_MIN) { //if less than item id, then potion
    invPtr = &player->potionInv;
    invNumPtr = &player->potionInvNum;
  }
  if(itemID < POTION_ID_MIN) { //if also less than potion id, then armor
    invPtr = &player->armorInv;
    invNumPtr = &player->armorInvNum;
  }
  if(itemID < ARMOR_ID_MIN) { //if also less than armor id, then weapon
    invPtr = &player->weaponInv;
    invNumPtr = &player->weaponInvNum;
  }
  struct InvNode* currNode = *invPtr; //points to head of inv list

  while(currNode != NULL) { //loop until end of list is reached
    if(currNode->item->id == itemID) { //node with desired item found
      if(currNode->prev != NULL) { //if currNode isn't first node
        currNode->prev->next = currNode->next; //update next of previous
      }
      else { //else currNode is first node
        *invPtr = currNode->next; //update head pointer
      }

      if(currNode->next != NULL) { //if currNode isn't last node
        currNode->next->prev = currNode->prev; //update previous of next
      }

      player->currInvSize -= currNode->item->size; //update inventory size
      (*invNumPtr)--; //update size of inv list

      if(currNode->item->type == ARMOR_TYPE) {
        player->currSpd += currNode->item->size / SIZE_SPD_FACTOR;
        player->currDef -= currNode->item->atk;
      }

      printf(RMV_FROM_INV_STR, currNode->item->name);
      
      free(currNode->item); //free item and node
      free(currNode);
      return 1; //return for successfully removing item
    }

    currNode = currNode->next; //desired item not found, jump to next node
  }
}
