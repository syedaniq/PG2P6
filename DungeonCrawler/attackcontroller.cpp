#include "attackcontroller.h"
#include <iostream>
#include "portal.h"

AttackController::AttackController(Level *level) : level(level)
{

}

int AttackController::move()
{
    rueckgabe.clear();
    convertPath();
    if(index % 3 == 0) {
        index++;
        return 5;
    }
    index++;
    if(rueckgabe.size()>0)
        return rueckgabe.at(0);
    else
        return 10;
}

void AttackController::convertPath()
{
    if(!level->getPlayer() or !level->getGoblin())
        rueckgabe.push_back(5);
    else {
        auto path = level->getPath(level->getGoblin()->getTile(),level->getPlayer()->getTile());
        for(size_t i=path.size()-1; i>0; i--)
        {
            std::cout << "PFAD: " << path.at(i)->getRow() << " / " << path.at(i)->getCol() << " ";
            rueckgabe.push_back(getMoveInt(path.at(i),path.at(i-1)));
            for(int i=0; i<rueckgabe.size(); i++)
                cout << "RUECKGABE: " << rueckgabe.at(i) << " ";
            cout << endl;
        }
    }
}

int AttackController::getMoveInt(Tile *from, Tile *to)
{
    int fromRow = from->getRow();
    int fromCol = from->getCol();
    int toRow = to->getRow();
    int toCol = to->getCol();

    if(typeid(*to) == typeid(Portal))
    {
        Portal* p = dynamic_cast<Portal*>(to);
        toRow = p->getDestination()->getRow();
        toCol = p->getDestination()->getCol();
    }

    int colAnderung = toCol - fromCol;
    int rowAnderung = toRow - fromRow;

    if(rowAnderung == 0)
    {
        if(colAnderung == -1)
            return 4;
        else if(colAnderung == 0)
            return 5;
        else if(colAnderung == 1)
            return 6;
    }
    else if(rowAnderung == 1)
    {
        if(colAnderung == -1)
            return 1;
        else if(colAnderung == 0)
            return 2;
        else if(colAnderung == 1)
            return 3;
    }
    else if(rowAnderung == -1)
    {
        if(colAnderung == -1)
            return 7;
        else if(colAnderung == 0)
            return 8;
        else if(colAnderung == 1)
            return 9;
    }
    else
        return 10;
}
