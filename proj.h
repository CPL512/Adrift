#ifndef PROJ_H
#define PROJ_H

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
//#include <strings.h> used for linux-builds
#include <ctype.h>

//Adrift respawn values
#define CUT_FACTOR 4
#define RETURN_TO_TOWN 1
#define REFIGHT 2

//Town options
#define TAVERN 1
#define SHOP 2
#define TALK 3
#define CONTINUE 4

//Tavern options
#define ROOM 1
#define DRINK 2
#define RUMORS 3
#define EXIT 4

//Shop options
#define BUY 1
#define SELL 2
#define LEAVE 3

#define WEAPON 1
#define ARMOR 2
//#define POTION 3 same as battle
#define SELL_PRICE_FACTOR 2

//Drink options
#define VIT 1
#define STR 2
#define FRT 3
#define AGI 4
#define DONE 5

//Travel options
#define FORWARD 1
#define INV 2
#define RET 3

#define BACK 0
//#define WEAPON 1  same as sell options
//#define ARMOR 2
//#define POTION 3
#define ITEM 4

//Battle options
#define ATTACK 1
#define GUARD 2
#define POTION 3

//Starting stats
#define START_HEALTH 5
#define START_ATK 3
#define START_DEF 3
#define START_SPD 3

//Effect of armor size on speed
#define SIZE_SPD_FACTOR 2

//Inventory sizes
#define DEF_INV_SIZE 5
#define SMALL_INV_SIZE 10
#define BIG_INV_SIZE 15

//Item ID ranges
#define ARMOR_ID_MIN 1000
#define POTION_ID_MIN 2000
#define ITEM_ID_MIN 3000

//attack hit chance values
#define HIT_CHANCE_FACTOR 90
#define HIT_CHANCE_MIN 10
#define HIT_CHANCE_MAX 100

//system values
#define BASE 10
#define MAX_INPUT_LENGTH 15
#define NAME_LENGTH 16 //including null terminator
#define NEWLINE_CHAR '\n'
#define NULL_CHAR '\0'

enum itemType { WEAPON_TYPE, ARMOR_TYPE, POTION_TYPE, ITEM_TYPE };

struct Player {
  char maxInvSize;
  char currInvSize;
  char weaponInvNum;
  char armorInvNum;
  char potionInvNum;
  char itemInvNum;
  int maxHealth;
  int currHealth;
  int baseAtk;
  int baseDef;
  int currDef;
  int baseSpd;
  int currSpd;
  int money;
  struct InvNode* weaponInv; //doubly-linked list
  struct InvNode* armorInv;
  struct InvNode* potionInv;
  struct InvNode* itemInv;
  char name[NAME_LENGTH];
};

struct InnKeep {
  char* actionPrompt;
  char* drinkPrompt;
  char* pricePrompt;
  char* rumors;
  char* exitMsg;
  char* invalidMsg;
  char* roomConfirm;
  char* drinkConfirm;
  char* insuffFunds;
  int brewPrice;
  int roomPrice;
};

struct ShopKeep {
  const char* buyPrompt;
  const char* sellPrompt;
  const char* buyOrSellPrompt;
  const char* typePrompt;
  const char* buyConfirm;
  const char* sellConfirm;
  const char* soldOutMsg;
  const char* insuffFunds;
  const char* insuffSpace;
  const char* invalidMsg;
  const char* exitMsg;
};

struct Item {
  char size;
  char* name;
  enum itemType type;
  int atk;
  int price;
  int id;
};

struct InvNode {
  struct Item* item;
  struct InvNode* next;
  struct InvNode* prev;
};

struct Enemy {
  char* name;
  int maxHealth;
  int currHealth;
  int atk;
  int def;
  int spd;
  int money;
};

int addItem( struct Player* playerPtr, char size, char* name, 
    enum itemType type, int atk, int price, int id );
int removeItem( struct Player* player, int itemID );
int hasItem( struct Player* player, int itemID );
void tavernAction( struct Player* player, struct InnKeep* keep );
void tavernSleep( struct Player* player );
void shopping( struct Player* player, int numItems,  struct Item shopInv[], int avail[] ); 
int battle( struct Player* player, struct Enemy* enemy );
void merriko(struct Player* p);
int toTellerian( struct Player* player );
long townAction();
long readInLong();
char readYesNo();
void printInv( struct Player* player, enum itemType type );

#endif
