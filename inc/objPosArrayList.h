#ifndef OBJPOSARRAYLIST_H
#define OBJPOSARRAYLIST_H

#include "objPosList.h"

#define DEFAULT_ARRAY_LIST_SIZE 1048576

// Public inheritance - using ObjPosList interface
class objPosArrayList : public objPosList
{
    private:
        objPos* list;
        int listSize;
        int arrayCapacity;
        int currentPos;

    public:
        objPosArrayList();
        virtual ~objPosArrayList();

        // Once inheriting interface (Pure Abstract Class), must provide concrete implementation
        // for all the interface functions.
        int getSize();
        bool isEmpty();

        void insertHead(const objPos &thisPos);
        void insertTail(const objPos &thisPos);
        void insert(const objPos &thisPos, int index);
        
        objPos getHead() const;
        objPos getTail() const;
        objPos get(int index) const;
        objPos getNext();
        void resetReadPos();
        void set(const objPos &thisPos, int index);

        objPos removeHead();
        objPos removeTail();
        objPos remove(int index);

        void printList() const;

};


#endif