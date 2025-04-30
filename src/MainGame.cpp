#include "MacUILib.h"
#include "GameMechs.h"
#include "ScreenDrawer.h"
#include "Player.h"
#include "ItemBin.h"

#include <chrono>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    // DECLARATION (LOCAL, on Stack)
    //////////////////////////////
    GameMechs *myGM;
    ScreenDrawer *myDrawer;
    Player* player1;
    ItemBin* myBin;


    // INITIALIZATION
    //////////////////////////////
    MacUILib_init();                            // Initialilze MacUI Library
    
    chrono::time_point<std::chrono::steady_clock> start, end;
    double totalTime = 0.0;
    int iterCount = 0;

    myGM = new GameMechs();                     // Create GM instance on the heap        
    myBin = new ItemBin(myGM);                  // Create the item bin on the heap
    player1 = new Player(3, 3, '@', myGM, myBin);      // Create first Player on the heap
    myDrawer = new ScreenDrawer(myGM, player1, myBin); // Create Screen Drawer Module on the heap
    
    myBin->generateItem();
   

    //////////////////////////////
    // PROGRAM LOOP
    //////////////////////////////
    while(myGM->getExitFlag() == false)
    {
        // I. GET INPUT
        myGM->processInput();
       
        // II. RUN LOGIC 
        start = std::chrono::steady_clock::now();  
        player1->movePlayer();
        end = std::chrono::steady_clock::now();
              
        // III. DRAW SCREEN  
        myDrawer->Draw();    

        std::chrono::duration<double, std::milli> elapsedTime = end - start;
        totalTime += elapsedTime.count();
        iterCount++;    
        
        myDrawer->DrawAverageComputationTime(totalTime / iterCount);        

        // IV. LOOP DELAY
        myGM->applyDelay();
    }



    // CLEANUP
    //////////////////////////////
    myDrawer->DrawEndGame();

    MacUILib_uninit();
    delete myGM;            // Remove GM instance on the heap
    delete myDrawer;
    delete player1;
    delete myBin;

    return 0;
}