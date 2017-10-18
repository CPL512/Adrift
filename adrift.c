/*
 * Filename: adrift.c
 * Author: Charles Li
 * Description: Handes adrift, the area the player goes upon death
 * Date: Jul 19 2017
 */

#include "proj.h"
#include "projStrings.h"

static const char first = 0;
static const char second = 1;

static char visitNum = 0;

int adrift( struct Player* player ) {
  long choice;

  if(visitNum == first) {
    Sleep(3);
    printf("\nMaurice: Oh, it's you again. Seems like you died again.\n");
    Sleep(1);
    printf("\nMaurice: You may be wondering what this place actually is.\n");
    Sleep(1);
    printf("\nMaurice: I've heard it called many things. Heaven. Hell. I call \
    it home.\n");
    Sleep(1);
    printf("\nMaurice: But people like you, people who don't stay dead, they \
    call it Adrift.\n");
    Sleep(1);
    printf("\nMaurice: Now, let's get down to business. I may be an immortal \
    undertaker for the souls of the dead, but I, too, enjoy my excursions \
    into the world of the living.\n");
    Sleep(2);
    printf("\nMaurice: As such, I'm going to need some coin if you want to \
    get back out there.\n");
    Sleep(1);
    printf("\nMaurice: Every time you die, I'll take a quarter of your vaz, \
    and if you have nothing, I'll take a quarter of your health instead.\n");
    Sleep(1);
    visitNum++;
  }
  else if(visitNum == second) {
    printf("\nMaurice: Hello again.\n");
    Sleep(1);
    printf("\nMaurice: You know, I've met a few people like you.\n");
    Sleep(1);
    printf("\nMaurice: Drifters. Show up on my doorstep, begging to be let \
    back into life.\n");
    Sleep(1);
    printf("\nMaurice: But I must say, you were the first to be in the state \
    I found you in.\n");
    Sleep(1);
    printf("\nMaurice: I wonder why that is.\n");
    Sleep(1);
    printf("\nMaurice: Anyway, about going back...\n");
    Sleep(1);
    visitNum++;
  }
  else {
    printf("\nMaurice: Welcome back. You know the drill.\n");
    Sleep(1);
  }

  if(player->money > 0) { //player has money
    if(player->money / CUT_FACTOR >= 1) { //quarter of money is at least 1
      printf(VAZ_REMOVED_STR, player->money / CUT_FACTOR);
      player->money -= player->money / CUT_FACTOR; //pay quarter of money
    }
    else { //1, 2, or 3 divided by 4 is 0, so pay 1 vaz
      printf(VAZ_REMOVED_STR, 1);
      player->money -= 1;
    }
    
    player->currHealth = player->maxHealth; //set player's health to full
  }
  else { //player has no money
    player->currHealth = player->maxHealth - player->maxHealth / CUT_FACTOR;
  }

  printf("\nMaurice: Pleasure doing business.\n");

  while(1) {
    Sleep(1);
    printf("\nMaurice: Do you want to return to the nearest town, or would you \
    rather have another go at whatever killed you?\n");
    printf(RESPAWN_OPT_STR);
    choice = readInLong();
  
    if(choice == RETURN_TO_TOWN) {
      printf("\nMaurice: Very well. Take care, %s.\n", player->name);
      Sleep(2);
      return 1;
    }
    else if(choice == REFIGHT) {
      printf("\nMaurice: Alright. Good luck, %s.\n", player->name);
      Sleep(2);
      return 0;
    }
    else {
      printf("\nMaurice: What?\n");
    }
  }
}
