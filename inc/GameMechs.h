#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include "Player.h"

#define MAX_PLAYER_COUNT 4

// Forward Declaration
class Player;

class GameMechs
{
    private:
        char** gameBoard;
        int boardSizeX;
        int boardSizeY;

        bool exitFlag;   
        bool loseFlag;     
        int delayConst;

        // Lab 3 - Queue
        // char* cmdQueue;
        //  Without this, no multiplayer can be carried out.
        char cmd;

        Player** playerList;     // array of player reference
        int playerCount;

        void setExitFlag();
        void setLoseFlag();
        void setInitBoard();
        bool checkInput();

    public:
        GameMechs();
        ~GameMechs();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        bool getExitFlag() const;
        bool getLoseFlag() const;
        char getCMD() const;
        char** getBoardRef() const;
        Player** getPlayerListRef() const;
        int getPlayerCount() const;
                
        void processInput();
        void applyDelay();

        void addPlayer(Player* pl);

        void setGameLost();
};

#endif