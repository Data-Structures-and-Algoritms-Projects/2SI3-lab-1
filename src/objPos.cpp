#include "objPos.h"
#include <iostream>
using namespace std;

objPos::objPos()
{
    x = 0;
    y = 0;
    number = 0;
    prefix = 0;
    symbol = 0;

    reward = 0;
}

objPos::objPos(int xp, int yp, int num, char pref, char s)
{
    x = xp;   
    y = yp;  
    number = num;  
    prefix = pref;  
    symbol = s;  

    reward = (number + prefix) * 3 / 2;
} 

objPos::objPos(const objPos& thisPos) // copy constructor
{
    x = thisPos.x; 
    y = thisPos.y; 
    number = thisPos.number; 
    prefix = thisPos.prefix; 
    symbol = thisPos.symbol; 

    reward = thisPos.reward;
} 

objPos& objPos::operator= (const objPos& thisPos)
{
    if(this != &thisPos)  
    {
        x = thisPos.x;      
        y = thisPos.y;      
        number = thisPos.number;      
        prefix = thisPos.prefix;      
        symbol = thisPos.symbol;      
        reward = thisPos.reward;
    }

    return *this;      
}


int objPos::getX() const
{
    return x; 
}

int objPos::getY() const
{
    return y;
}

int objPos::getNum() const
{
    return number;
}

char objPos::getPF() const
{
    return prefix;
}

char objPos::getSym() const
{
    return symbol;
}

int objPos::getReward() const
{
    return reward;
}


void objPos::setX(int xp)
{
    x = xp;
}

void objPos::setY(int yp)
{
    y = yp;
}

void objPos::setNum(int num)
{
    number = num % 100;  // cap at two-digits
}

void objPos::setPF(char pref)
{
    prefix = pref;
}

void objPos::setSym(char sym)
{
    symbol = sym;
}

void objPos::copyObjPos(objPos &thisPos)
{
    x = thisPos.x;
    y = thisPos.y;
    number = thisPos.number;
    prefix = thisPos.prefix;
    symbol = thisPos.symbol;
    reward = thisPos.reward;
}

bool objPos::isOverlap(const objPos* thisPos) const
{
    return (x == thisPos->getX() && y == thisPos->getY());  
}

void objPos::printObjPos() const
{
    cout << "(" << x << "," << y << "), " 
         << prefix << " " << number << " " << symbol << endl;
}


