#ifndef ITEMBIN_H
#define ITEMBIN_H

#include "objPos.h"
#include "objPosList.h"
#include "GameMechs.h"
#include "Player.h"

class GameMechs;
class Player;
class objPosList;

class ItemBin
{
    private:
        objPos* myItem;     // Lab 1/2 - Linked List / Array List
                            //  Discuss why No Real Performance Gain here.
        GameMechs* gmRef;
        char** boardRef;

        void undrawItem();
        void DigitToChar(char result[]); // pass by ref

    public:
        ItemBin(GameMechs* gm);
        ~ItemBin();

        void drawItem();
        void generateItem();
        objPos getItem();

        // Lab 3 - Stack
        // Generate 100 items, with pre-determined ranges of PF's and Nums
        //  So we can prep random food collections beforehand

        // Start - Use Array List
        // End - Use LL-based Stack
        // Performance Analysis
};

#endif