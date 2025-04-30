#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosList.h"
#include "ItemBin.h"


// Forward Declaration
class GameMechs;
class ItemBin;
class objPosList;

class Player
{
    private:
        GameMechs* gmRef;
        objPosList* myPos;  
        char** boardRef;
        ItemBin* binRef;
        int myScore;
        bool killable;

        enum Direction {STOP, UP, DOWN, LEFT, RIGHT};
        enum Direction myDir;
        
        void undrawPlayer();  // used to erase the player position on the board before calculating the new position
        bool checkCollision();
        bool checkSelfCollision();

        void updatePlayerFSM();        

    public:
        Player(int x, int y, char symbol, GameMechs* gm, ItemBin* bin);
        ~Player();
        
        void drawPlayer();
        void movePlayer();        
        void increaseScore();

        int getScore() const;

        objPosList* getPlayerPos() const;
};

#endif