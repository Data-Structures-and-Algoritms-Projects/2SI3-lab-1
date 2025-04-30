#include "Player.h"
#include "objPosArrayList.h"
//#include "objPosDLinkedList.h"

#include <iostream>
using namespace std;

#define TEST_LENGTH 1000

Player::Player(int x, int y, char symbol, GameMechs* gm, ItemBin* bin)
{
   
    // Choose the list type for Lab 2
    myPos = new objPosArrayList();       

    // turn false for performance estimation in Lab 2
    killable = true;  
    
    myPos->insertHead(objPos(x, y, -1, 0, symbol));
       
    gmRef = gm;
    boardRef = gmRef->getBoardRef();
    binRef = bin;

    myDir = STOP;
    myScore = 0;

    gmRef->addPlayer(this);
}

Player::~Player()
{
    delete myPos;
}


void Player::updatePlayerFSM()  // private
{
    char cmd = gmRef->getCMD();   
    switch(cmd)   
    {
        case 'w':
        case 'W':
            if(myDir != DOWN) myDir = UP;   
            break;

        case 's':
        case 'S':
            if(myDir != UP) myDir = DOWN;    
            break;

        case 'a':
        case 'A':
            if(myDir != RIGHT) myDir = LEFT;    
            break;

        case 'd':
        case 'D':
            if(myDir != LEFT) myDir = RIGHT;    
            break;

        default:
            break;    
    }
}   

void Player::movePlayer()
{    
    updatePlayerFSM();   // Theta(1)
    if(myDir == STOP) return;    //Theta(1)

    undrawPlayer(); //Theta(n)
    
    objPos currHeadPos = myPos->getHead();   //Theta(1)
    int inX = currHeadPos.getX();  //Theta(1)
    int inY = currHeadPos.getY();   //Theta(1)
        
    switch(myDir) 
    {
        case UP:            
            if(--inY < 1)  
                inY = gmRef->getBoardSizeY() - 2; //Theta(1)
            break;//Theta(1)

        case DOWN:
            if(++inY > (gmRef->getBoardSizeY() - 2)) 
                inY = 1;  //Theta(1)
            break;//Theta(1)

        case LEFT:
            if(--inX < 1)  
                inX = gmRef->getBoardSizeX() - 2; //Theta(1)
            break;//Theta(1)

        case RIGHT:
            if(++inX > (gmRef->getBoardSizeX() - 2)) 
                inX = 1;  //Theta(1)
            break;//Theta(1)

        default:
            break; //Theta(1)
    } 

    currHeadPos.setX(inX);        //Theta(1)       
    currHeadPos.setY(inY);// TARGET      //Theta(1)
    
    myPos->insertHead(currHeadPos);  // insert new head      //Theta_worst(n), Theta_best(1)

    if(!checkCollision())            // check collision.  If collision never happened,  
        myPos->removeTail();    //Theta(1)     // removeTail.  Otherwise, generate new item.    
    
    if(killable)        //ignore, always returns false                  
        if(checkSelfCollision())
            gmRef->setGameLost();       // If colliding with itself, end game.
     
     //T(overall) = Theta(n)
}    

    
bool Player::checkCollision()  // private
{    
    // 1. Check Item Bin for Item ObjPos
    objPos target = binRef->getItem();  
    bool collided = myPos->getHead().isOverlap(&target); 

    // 2. check whether objPos are equal
    if(collided)
    {
        // 3. If yes, collision takes place
        // Generate New Item(s)
        binRef->generateItem();

        // Increase Score by Number
        myScore += target.getNum();
    }

    return collided;
}

bool Player::checkSelfCollision()  // private
{    
    // Make sure snake is long enough to kill itself
    int length = myPos->getSize(); //Theta(1)
    if(length < 4) return false; //Theta(1)

    // Then check for self collision
    myPos->resetReadPos(); //Theta(1)
    objPos tempPos;  //Theta(1)
    objPos headPos = myPos->getNext(); //Theta(1)
    
    for(int i = 1; i < length; i++) //Theta(n)
    {
        tempPos = myPos->getNext();//Theta(1)
        if(headPos.isOverlap(&tempPos))
        {
            // set game end.
            return true; //Theta(1)
        }
    }

    return false; //Theta(1)

    //Theta_best(1)
    //Theta_worst(n)
    //O(n)
    //o(n^2)
}


void Player::drawPlayer()  
{
    objPos targetPos;  //Theta(1)
    int scanSize = myPos->getSize();  //Theta(1)  // get the list size  

    myPos->resetReadPos(); //Theta(1)
    for(int i = 0; i < scanSize; i++)  //Theta(n)
    {
        targetPos = myPos->getNext();  //Theta(1)
        boardRef[targetPos.getY()][targetPos.getX()] = targetPos.getSym();  //Theta(1)
    }  

    //T(overall) = Theta(n)
}  
    

void Player::undrawPlayer()  // private helper function
{
    objPos targetPos;  //Theta(1)
    int scanSize = myPos->getSize();  //Theta(1) // get the list size  
 
    myPos->resetReadPos();  //Theta(1)
    for(int i = 0; i < scanSize; i++) //Theta(n)
    {
        targetPos = myPos->getNext(); //Theta(1)
        boardRef[targetPos.getY()][targetPos.getX()] = ' ';  //Theta(1)
    }

    //T(overall) = Theta(n)
}  
    


void Player::increaseScore()
{
    myScore++;
}

int Player::getScore() const
{
    return myScore;    
}

objPosList* Player::getPlayerPos() const
{
    return myPos;   
}  
    
