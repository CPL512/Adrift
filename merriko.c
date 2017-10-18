/*
 * Filename: merriko.c
 * Author: Charles Li
 * Descriptions: Runs interactions in Merriko town
 * Date: June 28, 2017
 */

static void init(struct Player* p);
static void merrikoTavern();
static void merrikoShop();
static void merrikoTalk();

#include "proj.h"
#include "projStrings.h"
#include "projItems.h"

#define FIRST_VISIT 0
#define DELIVERING 1
#define DELIVERED 2
#define AFTER 3
#define PAY 5
#define SHOP_STOCK 2
#define GRETA 1
#define FAEN 2
#define RYN 3
#define LEAVE 4

/* NPC's */
static struct Player* player;
static struct InnKeep barnabas;
static struct ShopKeep fayn;

static struct Item shopInv[SHOP_STOCK];
static int avail[SHOP_STOCK];

static char tavState = FIRST_VISIT;
static char shopState = FIRST_VISIT;
static char initialized = 0;

void merriko( struct Player* p ) {
  if (!initialized) {
	init(p);
	initialized++;
  }

  int i;
  for(i = 0; i < SHOP_STOCK; i++) { //shop restocks every new visit to town
    avail[i] = 1;
  }

  printf("\nYou've arrived in Merriko town.\n");

  while(1) {
    switch(townAction()) {
      case TAVERN: //talk to barkeep, rest, level up
        merrikoTavern();
        break;
      case SHOP: //buy and sell equipment
        merrikoShop();
        break;
      case TALK: //talk to npc's, get and finish sidequests
        merrikoTalk();
        break;
      case CONTINUE: //move on to next area, fighting
        return;
    }
  }
}

static void init(struct Player* p) {
	player = p;

	/* NPC dialogue init */
	barnabas.actionPrompt = "\nBarnabas: What can I do for you?\n";
	barnabas.drinkPrompt = "\nWhat can I get started for you?\n";
	barnabas.pricePrompt = "\nBarnabas: A %s will cost you %i vaz. Are you sure?\n";
	barnabas.rumors = "\nBarnabas: Greta is my supplier for drink ingredients, but people like to gossip and say we are having an affair. Unfortunately for them, she is also my wife, so an affair would be rather strange.\n";
	barnabas.exitMsg = "\nBarnabas: Thank you for your patronage.\n";
	barnabas.invalidMsg = "Barnabas: I'm not sure what that means.\n";
	barnabas.roomConfirm = "\nBarnabas: Right this way.\n";
	barnabas.drinkConfirm = "\nBarnabas: Here you are. One %s\n";
	barnabas.insuffFunds = "\nBarnabas: My apologies, but it seems you don't have enough vaz.\n";
	barnabas.brewPrice = 5;
	barnabas.roomPrice = 10;

	fayn.buyPrompt = "\nFayn: Anything you want to take a look at?\n";
	fayn.sellPrompt = "\nFayn: Anything I can take off your hands?\n";
	fayn.buyOrSellPrompt = "\nFayn: Do you want to buy or sell?\n";
	fayn.typePrompt = "\nFayn: What type of item are you looking to sell?\n";
	fayn.buyConfirm = "\nFayn: That will cost %i vaz, Would you like to buy it?\n";
	fayn.sellConfirm = "\nFayn: I can pay you %i vaz for that %s. Is that alright?\n";
	fayn.soldOutMsg = "\nFayn: We're sold out of that, I'm afraid.\n";
	fayn.insuffFunds = "\nFayn: Sorry, but it doesn't look like you can afford that.\n";
	fayn.insuffSpace = "\nFayn: Looks like you've got too much stuff. I can buy some of that off of you.\n";
	fayn.invalidMsg = "\nFayn: I don't understand.\n";
	fayn.exitMsg = "\nFayn: Bye now, thanks for stopping by.\n";

	/* Shop inventory init */
	shopInv[0].size = TUNIC_SIZE;
	shopInv[0].name = TUNIC_NAME;
	shopInv[0].type = TUNIC_TYPE;
	shopInv[0].atk = TUNIC_DEF;
	shopInv[0].price = TUNIC_PRICE;
	shopInv[0].id = TUNIC_ID;

	shopInv[1].size = MIN_POT_SIZE;
	shopInv[1].name = MIN_POT_NAME;
	shopInv[1].type = MIN_POT_TYPE;
	shopInv[1].atk = MIN_POT_HEAL;
	shopInv[1].price = MIN_POT_PRICE;
	shopInv[1].id = MIN_POT_ID;
}

static void merrikoTavern() {
  switch(tavState) {
    case FIRST_VISIT:
      printf("\nBarnabas: Welcome, traveler. My name is Barnabas. A room for \
      the night is %i vaz ...", barnabas.roomPrice);
      Sleep(1);
      printf(" but you look like you just came back from death! So tell you \
      what, deliver this letter to Greta in town for me, and the room is on \
      the house, plus a little extra.\n");
      addItem(player, BARN_LETTER_SIZE, BARN_LETTER_NAME, BARN_LETTER_TYPE, 
          BARN_LETTER_ATK, BARN_LETTER_PRICE, BARN_LETTER_ID);
      tavState = DELIVERING;
      break;
    case DELIVERING:
      printf("\nBarnabas: Hello again! Have you delivered the letter yet? If \
      not, you should step to it. It's not everyday I offer a free room, you \
      know.\n");
      break;
    case DELIVERED:
      printf("\nBarnabas: Welcome back! Have you delivered the letter yet?\n");
      Sleep(1);
      printf("\nBarnabas: Ah, you have! Excellent. As promised, some vaz for \
      your troubles.");
      printf(VAZ_ADDED_STR, PAY);
      player->money += PAY;
      Sleep(1);
      printf("\nNow, right this way to your room.\n");
      tavernSleep(&player);
      break;
    case AFTER:
      printf("\nBarnabas: Welcome back, traveler.\n");
      break;
  }

  tavernAction(player, &barnabas);
}

static void merrikoShop() {
  if(shopState == FIRST_VISIT) {
    printf("\nFayn: Greetings! My name is Fayn. We don't have much in stock now, \
    but please take your time browsing, and let me know if you need any help.\n");
    shopState = AFTER;
  }
  else {
    printf("\nFayn: Hello again! As always, let me know if you need any help.\n");
  }

  shopping(player, SHOP_STOCK, shopInv, avail, &fayn);
}

static void merrikoTalk() {
  long choice = 0;

  while(1) {
    printf(TALK_PROMPT);
    printf("1. Greta\t2. Faen\t3. ???\t4. Leave\n");
    choice = readInLong();

    if(choice == GRETA) {
      if(tavState = FIRST_VISIT) {
        printf("\nGreta: Hello, my name is Greta, and welcome to Merriko town.");
      }
      else if(tavState == DELIVERING) {
        printf("\nGreta: Is that letter from Barny?\n");
        Sleep(1);
        removeItem(player, BARN_LETTER_ID);
        Sleep(1);
        printf("\nGreta: Ooohh, how exciting. Thank you for bringing this \
        to me.\n");
        tavState = DELIVERED;
      }
      else {
        printf("\nGreta: Thank you once again for delivering the letter to \
        me.");
        Sleep(1);
        printf("\nGreta: You've already met Barny, but did you know you can \
        also go to the shop and stock up on equipment and supplies?\n");
      }
    }
    else if(choice == FAEN) {
      printf("\nFaen: I'm Faen, and yes, Fayn is my twin sister.\n");
      Sleep(1);
      printf("\nFaen: Sometimes she teases me and says my name is wrong.");
      Sleep(1);
      printf("Sometimes I tell her to shut her dumb misspelled face.\n");
    }
    else if(choice == RYN) {
      printf("\n???: What.\n");
    }
    else if(choice == LEAVE) {
      return;
    }
    else {
      printf(INVALID_MSG);
    }
  }
}
