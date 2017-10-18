/*
 * Filename: tellerian.c
 * Author: Charles Li
 * Description: Runs interactions in Tellerian City
 * Date: Jul 20 2017
 */

static void init(struct Player* p);
static void tellerianTavern();
static void tellerianShop();
static void tellerianTalk();

#include "proj.h"
#include "projStrings.h"
#include "projItems.h"

#define FIRST_VISIT 0
#define UNFAMILIAR 1
#define FAMILIAR 2
#define DELIVERING 3
#define AFTER 4
#define SHOP_STOCK 5

#define NINLYTH 0
#define LETHO 1
#define JANSA 2
#define STUTTGAR 3
#define RYN 4
#define LEAVE 5

struct Player* player;
static struct InnKeep firstBriggs;
static struct InnKeep unfamBriggs;
static struct InnKeep famBriggs;
static struct ShopKeep morgan;

static struct Item shopInv[SHOP_STOCK];
static int avail[SHOP_STOCK];

static int tavState = FIRST_VISIT;
static int shopState = FIRST_VISIT;
static int stuttState = FIRST_VISIT;
static char initialized = 0;

void tellerian(struct Player* p) {
  if (!initialized) {
	init(p);
	initialized++;
  }
  
  int i;
  for(i = 0; i < SHOP_STOCK; i++) { //shop restocks every new visit to town
    avail[i] = 1;
  }

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

static void init(struct Player* p) {
	player = p;

	firstBriggs.actionPrompt = "\nBriggs: How can I help you?\n";
	firstBriggs.drinkPrompt = "\nBriggs: What would you like to have?\n";
	firstBriggs.pricePrompt = "\nBriggs: A %s costs %i vaz. Would you like one?\n";
	firstBriggs.rumors = "\nBriggs: I love my job! It pays well and my boss is lovely! I love my job!\n";
	firstBriggs.exitMsg = "\nBriggs: Thank you! Come again!\n";
	firstBriggs.invalidMsg = "Briggs: I'm sorry! I don't understand!\n";
	firstBriggs.roomConfirm = "\nBriggs: I'll show you to your room!\n";
	firstBriggs.drinkConfirm = "\nBriggs: Here is the %s you ordered!\n";
	firstBriggs.insuffFunds = "\nBriggs: I'm sorry! You don't have enough money!\n";
	firstBriggs.brewPrice = 7;
	firstBriggs.roomPrice = 10;

	unfamBriggs.actionPrompt = "\nBriggs: How can I help you?\n";
	unfamBriggs.drinkPrompt = "\nBriggs: What would you like to have?\n";
	unfamBriggs.pricePrompt = "\nBriggs: A %s costs %i vaz. Would you like one?\n";
	unfamBriggs.rumors = "\nBriggs: Truth be told, I hate this job. Little pay for grueling work, dealing with dumb customers all day. And always with a smile on your face! It sucks.\n";
	unfamBriggs.exitMsg = "\nBriggs: Thank you! Come again!\n";
	unfamBriggs.invalidMsg = "Briggs: I'm sorry! I don't understand!\n";
	unfamBriggs.roomConfirm = "\nBriggs: I'll show you to your room!\n";
	unfamBriggs.drinkConfirm = "\nBriggs: Here is the %s you ordered!\n";
	unfamBriggs.insuffFunds = "\nBriggs: I'm sorry! You don't have enough money!\n";
	unfamBriggs.brewPrice = 7;
	unfamBriggs.roomPrice = 10;

	famBriggs.actionPrompt = "\nBriggs: What do you need?\n";
	famBriggs.drinkPrompt = "\nBriggs: What drink?\n";
	famBriggs.pricePrompt = "\nBriggs: %s is %i vaz. Want it?\n";
	famBriggs.rumors = "\nBriggs: Yeah, this still sucks. At least I don't need some facade with you.\n";
	famBriggs.exitMsg = "\nBriggs: See ya.\n";
	famBriggs.invalidMsg = "Briggs: What?\n";
	famBriggs.roomConfirm = "\nBriggs: Your room's over there.\n";
	famBriggs.drinkConfirm = "\nBriggs: Here, one %s.\n";
	famBriggs.insuffFunds = "\nBriggs: Not enough money, pal.\n";
	famBriggs.brewPrice = 7;
	famBriggs.roomPrice = 10;

	morgan.buyPrompt = "\nMorgan: Buy, buy, buy! We got it all, for the best prices, here at Morgans!\n";
	morgan.sellPrompt = "\nMorgan: Sell, sell, sell! I love selling stuff, and I love buying stuff too!\n";
	morgan.buyOrSellPrompt = "\nMorgan: Are you giving me money, or am I giving you money?\n";
	morgan.typePrompt = "\nMorgan: What kind of stuff do you want great deals on today?\n";
	morgan.buyConfirm = "\nMorgan: That costs %i vaz. A great deal in my book! Want to buy it?\n";
	morgan.sellConfirm = "\nMorgan: I can give you %i vaz for your %s. I'm practically handing you my money! Want to sell it?\n";
	morgan.soldOutMsg = "\nMorgan: Ooh, can't sell you that one, I'm afraid. It's sold out!\n";
	morgan.insuffFunds = "\nMorgan: Sorry, but this deal is already too much! Any more, and I'll be broke within days!\n";
	morgan.insuffSpace = "\nMorgan: Not enough room for that one. Sell some of your stuff to me for great prices, and then try again!\n";
	morgan.invalidMsg = "\nMorgan: That wasn't in the language of deals, I'm afraid!\n";
	morgan.exitMsg = "\nMorgan: Come back when you want more deals!\n";

	shopInv[0].size = BROADSWORD_SIZE;
	shopInv[0].name = BROADSWORD_NAME;
	shopInv[0].type = BROADSWORD_TYPE;
	shopInv[0].atk = BROADSWORD_ATK;
	shopInv[0].price = BROADSWORD_PRICE;
	shopInv[0].id = BROADSWORD_ID;

	shopInv[1].size = DAGGER_SIZE;
	shopInv[1].name = DAGGER_NAME;
	shopInv[1].type = DAGGER_TYPE;
	shopInv[1].atk = DAGGER_ATK;
	shopInv[1].price = DAGGER_PRICE;
	shopInv[1].id = DAGGER_ID;

	shopInv[2].size = LHELMET_SIZE;
	shopInv[2].name = LHELMET_NAME;
	shopInv[2].type = LHELMET_TYPE;
	shopInv[2].atk = LHELMET_DEF;
	shopInv[2].price = LHELMET_PRICE;
	shopInv[2].id = LHELMET_ID;

	shopInv[3].size = MIN_POT_SIZE;
	shopInv[3].name = MIN_POT_NAME;
	shopInv[3].type = MIN_POT_TYPE;
	shopInv[3].atk = MIN_POT_HEAL;
	shopInv[3].price = MIN_POT_PRICE;
	shopInv[3].id = MIN_POT_ID;

	shopInv[4].size = MID_POT_SIZE;
	shopInv[4].name = MID_POT_NAME;
	shopInv[4].type = MID_POT_TYPE;
	shopInv[4].atk = MID_POT_HEAL;
	shopInv[4].price = MID_POT_PRICE;
	shopInv[4].id = MID_POT_ID;
}

static void tellerianTavern() {
  if(tavState == FIRST_VISIT) {
    printf("\nBriggs: Hello, traveler! My name is Briggs! We have rooms, \
    drinks, and more! If you need anything, just ask!\n");
    tavState = UNFAMILIAR;

    tavernAction( player, &firstBriggs );
  }
  else if(tavState == UNFAMILIAR) {
    printf("\nBriggs: Hello again, traveler! Once again, let me know if you \
    want anything!\n");
    tavState = FAMILIAR;

    tavernAction( player, &unfamBriggs );
  }
  else if(tavState == FAMILIAR) {
    printf("\nBriggs: Oh, it's you again. Want anything, so on and so forth, \
    wake me up if you need me.\n");

    tavernAction( player, &famBriggs );
  }
}

static void tellerianShop() {
  if(shopState == FIRST_VISIT) {
    printf("\nMorgan: Weapons, armor, and potions. We have what you want, we \
    have what you need. When you think of equipment, you think of Morgan's!\n");
    shopState = AFTER;
  }
  if(shopState == DELIVERING) {
    printf("\nMorgan: A letter from Stuttgar?\n");
    Sleep(1);
    removeItem( player, STUTT_LETTER_ID );
    Sleep(1);
    printf("\nMorgan: More supplies?!\n");
    Sleep(1);
    printf("\nMorgan: This letter you delivered is from Stuttgar, my supplier. \
    He says he has more supplies than usual this month. And more supplies \
    means more deals!\n");
    Sleep(1);
    printf("\nMorgan: To celebrate, take this potion, on me!\n");
    addItem(player, MID_POT_SIZE, MID_POT_NAME, MID_POT_TYPE, MID_POT_HEAL,
    MID_POT_PRICE, MID_POT_ID);
    shopState = AFTER;
    stuttState = AFTER;
  }
  else if(shopState == AFTER) {
    printf("\nMorgan: Hey there. Didn't get enough deals, deals, deals? Then \
    you've come to the right place!\n");
  }

  shopping( player, SHOP_STOCK, shopInv, avail, &morgan ); 
}

void tellerianTalk() {
  long choice = 0;

  while(1) {
    printf(TALK_PROMPT);
    printf("1. Ninlyth\t2. Letho\t3. Jansa \t4. Stuttgar\t5. ???\t6. Leave\n");
    choice = readInLong();

    if(choice == NINLYTH) {
      printf("\nNinlyth: You should try talking to Briggs in the tavern. He \
      just might open up to you.\n");
    }
    else if(choice == LETHO) {
      printf("\nLetho: Welcome to Tellerian, where the sun goes to bed before \
      we do. In a city as big as this, I'd be surprised if you ran out of \
      things to do.\n");
    }
    else if(choice == JANSA) {
      printf("\nJansa: Look at Letho. He's so dreamy and nice. I'll bet he \
      welcomed you to the city.\n");
    }
    else if(choice == STUTTGAR) {
      if(stuttState = FIRST_VISIT) {
        printf("\nStuttgar: Give this letter to Morgan, would you? He'll make \
        it worth your while.\n");
	      addItem( player, STUTT_LETTER_SIZE, STUTT_LETTER_NAME, 
            STUTT_LETTER_TYPE, STUTT_LETTER_ATK, STUTT_LETTER_PRICE, 
            STUTT_LETTER_ID);
        shopState = DELIVERING;
	      stuttState = DELIVERING;
      }
      else if(stuttState = DELIVERING) {
        printf("\nStuttgar: Haven't delivered the letter yet? Trust me, you'll \
	want to.\n");
      }
      else if(stuttState == AFTER) {
        printf("\nStuttgar: Thanks for delivering the letter. Safe travels and \
	good deals be with you.\n");
      }
    }
    else if(choice == RYN) {
      printf("???: Mind your own business.");
    }
    else if(choice == LEAVE) {
      return;
    }
    else {
      printf(INVALID_MSG);
    }
  }
}

