/* Filename: addItem.c
 * Author: Charles Li
 * Description: Checks if the specified item can be added to the player's
 *              inventory, and adds it if it can.
 * Date: June 27, 2017
 */

#include <stdlib.h>
#include "proj.h"
#include "projStrings.h"

int addItem( struct Player* playerPtr, char size, char* name, enum itemType type, int atk, int price, int id ) {
  if(playerPtr->currInvSize + size > playerPtr->maxInvSize) { //item too large
    return 0; //return false, item not added
  }
  else { //item fits, add it
    struct InvNode** invPtr; //will point to an inventory pointer
    char* invNumPtr;
    switch(type) { //determine which inventory list item goes to
      case WEAPON:
        invPtr = &playerPtr->weaponInv;
        invNumPtr = &playerPtr->weaponInvNum;
        break;
      case ARMOR:
        invPtr = &playerPtr->armorInv;
        invNumPtr = &playerPtr->armorInvNum;
        break;
      case POTION:
        invPtr = &playerPtr->potionInv;
        invNumPtr = &playerPtr->potionInvNum;
        break;
      case ITEM:
        invPtr = &playerPtr->itemInv;
        invNumPtr = &playerPtr->itemInvNum;
        break;
    }

    struct InvNode* node = malloc(sizeof(struct InvNode));
    struct Item* item = malloc(sizeof(struct Item));
    item->size = size; //init item's size
    item->name = name; //init item's name
    item->type = type; //init item's type
    item->atk = atk; //init item's atk
    item->price = price; //init item's price
    item->id = id; //init item's id
    node->item = item;
    if(*invPtr == NULL) { //init first node of inventory linked list
      node->next = NULL;
      node->prev = NULL;
      *invPtr = node;
    }
    else { //add item to head of linked list
      node->next = *invPtr;
      node->prev = NULL;
      node->next->prev = node; //update previous pointer of old head
      *invPtr = node; //update head pointer
    }
    playerPtr->currInvSize += size; //increase player's current inventory size
    (*invNumPtr)++;
    
    if(type == ARMOR) {
      playerPtr->currSpd -= size / SIZE_SPD_FACTOR;
      playerPtr->currDef += atk;
    }

    printf(ADD_TO_INV_STR, name);

    return 1; //return true, item added
  }
}
