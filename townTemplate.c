/*
 * Filename: tellerian.c
 * Author: Charles Li
 * Description: Runs interactions in Tellerian City
 * Date: Jul 20 2017
 */

#include "proj.h"
#include "projStrings.h"

#define FIRST_VISIT 0
#define AFTER 3
#define SHOP_STOCK 5

struct Player* player;
static struct InnKeep {
  actionPrompt = "\n\n";
  drinkPrompt = "\n\n";
  pricePrompt = "\n %s %i \n";
  rumors = "\n\n";
  exitMsg = "\n\n";
  invalidMsg = "\n";
  roomConfirm = "\n\n";
  drinkConfirm = "\n %s \n";
  insuffFunds = "\n\n";
  brewPrice = 7;
  roomPrice = 10;
}

static struct ShopKeep {
  buyPrompt = "\n\n";
  sellPrompt = "\n\n";
  buyOrSellPrompt = "\n\n";
  typePrompt = "\n\n";
  buyConfirm = "\n %i \n";
  sellConfirm = "\n %i  %s \n";
  soldOutMsg = "\n\n";
  insuffFunds = "\n\n";
  insuffSpace = "\n\n";
  invalidMsg = "\n\n";
  exitMsg = "\n\n";
}

static struct Item shopInv[SHOP_STOCK];
static int avail[SHOP_STOCK];

static int tavState = 0;
static int shopState = 0;

void tellerian(struct Player* p) {
  player = p;

  printf("\nYou've arrived in Tellerian City.\n");

  while(1) {
    switch(townAction()) {
      case TAVERN:
        tellerianTavern();
        break;
      case SHOP:
        tellerianShop();
        break;
      case TALK:
        tellerianTalk();
        break;
      case CONTINUE:
        return;
    }
  }
}

void tellerianTavern() {
}

void tellerianShop() {
}

void tellerianTalk() {
}
