/*
 * Filename: shopping.c
 * Author: Charles Li
 * Description: Handles shop interaction, allowing the player to buy and sell
 * items and equipment.
 * Date: Jul 10 2017
 */

#include "proj.h"
#include "projStrings.h"

void shopping( struct Player* player, int numItems, struct Item shopInv[], int avail[], struct ShopKeep* keep ) {
  int i;
  long choice;
  char yesNo;

  while(1) {
    printf(keep->buyOrSellPrompt);
    choice = readInLong();

    if(choice == BUY) {
      while(1) {
        printf(EXIT_OPT); //print exit option 0. Never mind
        for(i = 0; i < numItems; i++) { //loop through all items in shopInv
          printf("%i. %s ", i+1, shopInv[i].name); //print number and name
          if(avail[i]) { //followed by either price if it's available
            printf("%i\n", shopInv[i].price);
          }
          else { //or "Sold" if it's not
            printf("%s\n", SOLD_STR);
          }
        }

        printf(keep->buyPrompt); //prompt player for item choice or exit
        choice = readInLong();
        if(!choice) { //if 0, break out of buy loop
          break;
        }
        else if(choice < 0 || choice > numItems) { //if < 0 or > numItems, invalid
          printf(keep->invalidMsg);
        }
        else { //otherwise, check item's availability
          choice--; //index is 1 less than number

          if(avail[choice]) { //item is available
            while(1) {
              printf("\n%s %i %i", shopInv[choice].name, shopInv[choice].size, 
                  shopInv[choice].atk); //print more item info
              printf(keep->buyConfirm, shopInv[choice].price);
              yesNo = readYesNo();
  
              if(yesNo == 1) { //yes, would like to buy
                if(player->money < shopInv[choice].price) { //insufficient funds
                  printf(keep->insuffFunds);
                  break; //not enough money, no need to reprompt for purchase
                }
                else if(player->currInvSize + shopInv[choice].size > 
                    player->maxInvSize) { //insufficient inventory space
                  printf(keep->insuffSpace);
                  break; //not enough space, no need to reprompt for purchase
                }
                else { //enough money and space
                  player->money -= shopInv[choice].price; //player pays price
                  printf(VAZ_REMOVED_STR, shopInv[choice].price);
                  addItem(player, shopInv[choice].size, shopInv[choice].name,
                      shopInv[choice].type, shopInv[choice].atk, 
                      shopInv[choice].price, shopInv[choice].id); //add item to inv
                  printf(ADD_TO_INV_STR, shopInv[choice].name);
                  avail[choice] = 0; //item purchased, no longer available
                  break; //item purchased, no need to reprompt for purchase
                }
              }
              else if(yesNo == 0) { //no, would not like to buy
                break; //no need to reprompt for purchase
              }
              else { //invalid input
                printf(keep->invalidMsg); //no break, reprompt for purchase
              }
            }
          }
          else{ //item isn't available, print message and loop back to reprompt
            printf("%s", keep->soldOutMsg);
          }
        }
      }
    }
    else if(choice == SELL) { //sell selected
      while(1) {
        struct InvNode** invPtr;
        char* invNumPtr;
        enum itemType type;

        printf(keep->typePrompt); //prompt for type of item to sell
        printf(TYPE_STR);
        choice = readInLong();

        if(!choice) { //choice = 0, break type loop and reprompt buy or sell
          break;
        }
        else if(choice == WEAPON) { //weapon, set pointers to weapon inv
          invPtr = &player->weaponInv;
          invNumPtr = &player->weaponInvNum;
          type = WEAPON_TYPE;
        }
        else if(choice == ARMOR) { //armor, set pointers to armor inv
          invPtr = &player->armorInv;
          invNumPtr = &player->armorInvNum;
          type = ARMOR_TYPE;
        }
        else if(choice == POTION) { //potion, set pointers to potion inv
          invPtr = &player->potionInv;
          invNumPtr = &player->potionInvNum;
          type = POTION_TYPE;
        }
        else { //none of the above, print invalid and reprompt for type
          printf(keep->invalidMsg);
          continue;
        }
        
        while(1) {
          printf(EXIT_OPT); //print 0. Never mind for exit option
          printInv(player, type); //print items in specified inventory
          printf(keep->sellPrompt); //prompt player for what to sell
          choice = readInLong();

          if(!choice) { //if 0, break sell loop and reprompt for type
            break;
          }
          else if(choice < 0 || choice > *invNumPtr) { //invalid input
            printf(keep->invalidMsg);
          }
          else { //item selected
            int j;
            struct InvNode* currNode = *invPtr;

            for( j = 1; j < choice; j++ ) { //iterate to the node of the item
              currNode = currNode->next;
            }

            while(1) { //loop to account for invalid input
              printf(keep->sellConfirm, currNode->item->price / SELL_PRICE_FACTOR, 
                  currNode->item->name);
              yesNo = readYesNo();
          
              if(yesNo == 1) { //yes, would like to sell
                player->money += currNode->item->price / SELL_PRICE_FACTOR;
                printf(VAZ_ADDED_STR, currNode->item->price / SELL_PRICE_FACTOR);
                removeItem(player, currNode->item->id); //give player money,
                break; //print msg, remove item, and break out of loop
              }
              else if(yesNo == 0) { //no, would not like to sell
                break; //break out of loop
              }
              else { //invalid input
                printf(keep->invalidMsg); //loop back up to reprompt for sell
              }
            }
          }
        }
      }
    }
    else if(choice == LEAVE) { //leave selected, print msg and exit function
      printf(keep->exitMsg);
      return;
    }
    else { //not buy, sell, or leave, so invalid
      printf(keep->invalidMsg);
    }
  }
}
