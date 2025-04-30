#include "ItemBin.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

ItemBin::ItemBin(GameMechs* gm)
{
    gmRef = gm;
    boardRef = gmRef->getBoardRef();  
    myItem = new objPos(12, 12, 32, 'A', '*');  

    srand(time(NULL));    
}

ItemBin::~ItemBin()
{
    delete myItem;
}

void ItemBin::drawItem()
{
    int x = myItem->getX();    
    int y = myItem->getY();     
    char num[2];  // convert number to displayable chars     
    DigitToChar(num);    

    boardRef[y][x] = myItem->getSym();    
    boardRef[y-1][x-1] = myItem->getPF();    
    boardRef[y-1][x] = num[0];    
    boardRef[y-1][x+1] = num[1];    
}      

void ItemBin::undrawItem()
{
    int x = myItem->getX();   
    int y = myItem->getY();

    boardRef[y][x] = ' ';
    boardRef[y-1][x-1] = ' ';
    boardRef[y-1][x] = ' ';
    boardRef[y-1][x+1] = ' ';
}

void ItemBin::DigitToChar(char result[])
{
    int number = myItem->getNum();     
    result[0] = (number / 10) + '0';      
    result[1] = (number % 10) + '0';    
}    


void ItemBin::generateItem()
{
    // Step 1: Get Player Ref from GameMech for Player pos
    Player** plList = gmRef->getPlayerListRef();      //Theta(1)    
    objPosList *playerPos = plList[0]->getPlayerPos();    //Theta(1)

    //int bitVec[gmRef->getBoardSizeX()][gmRef->getBoardSizeY()]= {0};

    // to prevent stack overflow
    int xsize = gmRef->getBoardSizeX();//Theta(1)
    int ysize = gmRef->getBoardSizeY();//Theta(1)
    int** bitVec = new int*[xsize];//Theta(1)
    for(int i = 0; i < xsize; i++) //Theta(n)
    {
        bitVec[i] = new int[ysize];//Theta(1)
        for(int j = 0; j < ysize; j++) //Theta(n)
            bitVec[i][j] = 0; //Theta(1)
    }
       


    int playerLength = playerPos->getSize();    //Theta(1)

    objPos target;  //Theta(1)
    playerPos->resetReadPos(); //Theta(1)

    for(int i = 0; i < playerLength; i++) //Theta(n)
    {
        target = playerPos->getNext();  //Theta(1)
        bitVec[target.getX()][target.getY()] = 1;    //Theta(1)   
    }    

    int randCandidateX = 0; //Theta(1)
    int randCandidateY = 0;//Theta(1)
    int randCandidate = 0;//Theta(1)

    // Step 2: Generate another food object
    // Coordinate Generation
    // x [2, BoardX-3]
    // y [2, BoardY-3]   

    do
    {
        randCandidateX = rand() % (gmRef->getBoardSizeX() - 4) + 2; //rand produces big_omega(1)
        randCandidateY = rand() % (gmRef->getBoardSizeY() - 4) + 2; //rand produces big_omega(1)
    } while(bitVec[randCandidateX][randCandidateY] != 0); //big_omega(1)
    

    undrawItem(); //Theta(1)

    myItem->setX(randCandidateX);//Theta(1)
    myItem->setY(randCandidateY);     //Theta(1)

    // Prefix Generation
    // PF   [a-z, A-Z]
    randCandidate = rand() % 26 + 'A';  // 26 alpabets          //Theta(1)
    if(rand() % 2) randCandidate += 32; // randomly lowercased 
    myItem->setPF((char)randCandidate); //Theta(1)

    // Number Generation
    // Number [00, 99]
    myItem->setNum(rand() % 100);   //Theta(1)

    drawItem();//Theta(1)

    for(int i = 0; i < xsize; i++)//Theta(n)
        delete[] bitVec[i];//Theta(1)
    delete[] bitVec;//Theta(1)

    //T(overall) = big_omega(n^2)
}


objPos ItemBin::getItem()
{
    objPos temp(myItem->getX(), myItem->getY(), myItem->getNum(), myItem->getPF(), myItem->getSym());
    // constructor     
    return temp;  // copy constructor     
}   
