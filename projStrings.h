/*
 * Filename: projStrings.h
 * Author: Charles Li
 * Description: Defines string constants for use in functions
 * Date: Jun 30 2017
 */

/* System messages */
 #define ADD_TO_INV_STR "\n* %s added to inventory *\n"
 #define RMV_FROM_INV_STR "\n* %s removed from inventory *\n"
 #define VAZ_ADDED_STR "\n* %i vaz added *\n"
 #define VAZ_REMOVED_STR "\n* %i vaz removed *\n"

/* Respawn */
 #define RESPAWN_OPT_STR "1. Return to town\t2. Refight\n"

/* Town */
 #define TOWN_ACTIONS_PROMPT "\nWhat do you do?\n"
 #define TOWN_ACTIONS_STR "1. Tavern\t2. Shop\t3. Talk\t4. Continue\n"
 #define INVALID_MSG "Invalid\n"

/* Tavern */
 #define TAVERN_ACTIONS_STR "1. Room\t2. Drink\t3. Rumors\t4. Exit\n"
 #define ROOM_NAME "room"
 #define DRINK_NAME "drink"
 #define HEALED_MSG "* Health restored to full *\n"
 #define DRINKS_STR "1. Vitality\t2. Strength\t3. Fortitude\t4. Agility\n"
 #define VIT_BREW "Vitality Brew"
 #define STR_BREW "Strength Brew"
 #define FRT_BREW "Fortitude Brew"
 #define AGI_BREW "Agility Brew"

/* Shop */
 #define BUY_SELL_STR "1. Buy\t2. Sell\t3. Exit\n"
 #define TYPE_STR "0. Never mind\t1. Weapon\t2. Armor\t3. Potion\n"
 #define SOLD_STR "Sold"
 #define EXIT_OPT "\n0. Never mind\n"

/* Talk */
 #define TALK_PROMPT "\nWho would you like to talk to?\n"

/* Travel */
 #define TRAVEL_PROMPT "\nWhat do you do?\n"
 #define TRAVEL_OPT_STR "1. Continue\t2. Inventory\t3. Return\n"
 #define CHECK_INV_PROMPT "\nWhich inventory do you check?\n"
 #define CHECK_INV_STR "0. Back\t1. Weapon\t2. Armor\t3. Potion\t4. Item\n"
 #define CONFIRM_POT_PROMPT "\nUse a potion?\n"

/* Battle */
 #define BATTLE_PROMPT "\nWhat do you do?\n"
 #define BATTLE_OPT_STR "1. Attack\t2. Guard\t3. Potion\n"
 #define WEAPON_PROMPT "\nWhich weapon do you use?\n"

/* Use potion */
 #define POTION_PROMPT "\nWhich potion do you use?\n"
 #define POTION_HEAL_STR "\n* Healed for %i health *\n"

/* Battle messages */
 #define ATK_STR "\n* You attack with %s *\n"
 #define ENEMY_STR "\n* %s attacks *\n"
 #define DAMAGE_STR "\n* %s hit for %i damage *\n"
 #define MISSED_STR "\n* The attack misses *\n"
 #define PLAYER_STR "You were"
 #define DEFEAT_STR "\n* %s defeated *\n"
 #define ENEMY_DROPPED_VAZ "\n* %s dropped %i vaz *\n"
