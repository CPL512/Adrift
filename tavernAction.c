/*
 * Filename: tavernAction.c
 * Author: Charles Li
 * Description: Prompts the player for their choice of action while in a tavern
 * Date: Jun 30 2017
 */

#include "proj.h"
#include "projStrings.h"

void tavernAction( struct Player* player, struct InnKeep* keep ) {
  long choice = 0;
  char yesNo = 0;

  while(1) {
	char* drinkName;

	printf(keep->actionPrompt);
	printf(TAVERN_ACTIONS_STR);
	choice = readInLong();
	if(choice != ROOM && choice != DRINK && choice != RUMORS && choice != EXIT) { //if not one of 4 valid choices
	  printf(keep->invalidMsg); //print invalid message and reprompt
	  continue;
	}
    switch(choice) { //valid choice, switch depending on choice
      case ROOM:
        while(1) {
          printf(keep->pricePrompt, ROOM_NAME, keep->roomPrice);
          yesNo = readYesNo();

          if(yesNo == 1) { //yes, wants room
            if(player->money >= keep->roomPrice) { //enough money
              player->money -= keep->roomPrice; //pay price
              printf("* %i vaz remaining *", player->money);
              printf(keep->roomConfirm); //print confirmation message
              tavernSleep(player); //restore health and print message
            }
            else { //insufficient funds
              printf(keep->insuffFunds);
              break; //no need to reprompt room, loop back to reprompt action
            }
          }

          else if(yesNo == 0) { //no, doesn't want room
            break; //loop back to reprompt action
          }

          else { //invalid input, reprompt room
            printf(keep->invalidMsg);
          }
        }
        break; //room actions done, break from switch, reprompt for action choice
      case DRINK:
        while(1) { //allow player to continue drinking after first drink
          printf(keep->drinkPrompt); //prompt for drink choice
          printf(DRINKS_STR);
          choice = readInLong;
          
          if(choice == VIT || choice == STR || choice == FRT || choice == AGI) {
            
            /* Save drink name according to selection */
            if(choice == VIT) { 
              drinkName = VIT_BREW;
            }
            else if(choice == STR) {
              drinkName = STR_BREW;
            }
            else if(choice == FRT) {
              drinkName = FRT_BREW;
            }
            else if(choice == AGI) {
              drinkName = AGI_BREW;
            }

            /* Prompt the player for money and check for funds */
            printf(keep->pricePrompt, drinkName, keep->brewPrice);
            yesNo = readYesNo();
            if(yesNo == 1) { //yes, want the drink
              if(player->money >= keep->brewPrice) { //enough money
                player->money -= keep->brewPrice;
                printf("* %i vaz remaining *", player->money);
                printf(keep->drinkConfirm, drinkName); //print confirm message
                
                /* Increase corresponding stat */
                if(choice == VIT) {
                  player->maxHealth++;
                  player->currHealth++;
                  printf("\n* Vitality increased *\n");
                }
                else if(choice == STR) {
                  player->baseAtk++;
                  printf("\n* Strength increased *\n");
                }
                else if(choice == FRT) {
                  player->baseDef++;
                  printf("\n* Fortitude increased *\n");
                }
                else if(choice == AGI) {
                  player->baseSpd++;
                  printf("\n* Agility increased *\n");
                }
              }
              else { //insufficient funds
                printf(keep->insuffFunds);
                break; //no need to keep prompting if no money
              }
            }
            else { //don't want the drink or invalid input
              continue; //reprompt for drink choice
            }
          }
          else if(choice == DONE) { //no more drinks, break out of loop
            break; //loop back for action choice
          }
          else { //invalid input, reprompt drink choice
            printf(keep->invalidMsg);
          }
        }
        break; //drink actions done, break from switch, reprompt for action choice
      case RUMORS:
        printf(keep->rumors);
		break; //break from switch, reprompt for action choice
      case EXIT:
        printf(keep->exitMsg);
        return;
    }
  }
}
