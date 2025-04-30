#include "ScreenDrawer.h"
#include "MacUILib.h"

ScreenDrawer::ScreenDrawer(GameMechs* gm, Player* player, ItemBin* bin)
{
    gmRef = gm;
    playerRef = player;
    binRef = bin;
}

ScreenDrawer::~ScreenDrawer()
{
    // No heap member, nothing to delete here
}

void ScreenDrawer::Draw() const
{
    // Clear the Screen
    MacUILib_clearScreen(); //Theta(1)

    // redraw all items;    
    binRef->drawItem();  //Theta(1)   
    playerRef->drawPlayer();  //Theat(1)

    // Get the Game Board 2D array
    char** drawTarget = gmRef->getBoardRef();  //Theta(1)
    objPos target = binRef->getItem();  //Theta(1)       
    
    // Draw it on the screen
    for(int i = 0; i < gmRef->getBoardSizeY(); i++)   //Theta(n)
    {
        for(int j = 0; j < gmRef->getBoardSizeX(); j++)  //Theta(n)
        {
            MacUILib_printf("%c", drawTarget[i][j]); //Theta(1)  
        }
        MacUILib_printf("\n"); //Theta(1)
    }

    // Append any required debugging message below
    MacUILib_printf("Player Score: %d\n", playerRef->getScore());  //Theta(1)
    MacUILib_printf("Food Reward: %d\n", target.getReward()); //Theta(1)
    //MacUILib_printf("Object: <%d, %d>, ID=%c%d\n", target.getX(), target.getY(), target.getPF(), target.getNum());       

    //T(overall) = Theta(n^2) 
}  

void ScreenDrawer::DrawEndGame() const
{
    if(gmRef->getLoseFlag())
        MacUILib_printf("You have Lost!\n");
    else
        MacUILib_printf("Game Shuts Down\n");
}

void ScreenDrawer::DrawAverageComputationTime(double data) const
{
    MacUILib_printf("Average Computation Time: %.10f ms\n", data);
}