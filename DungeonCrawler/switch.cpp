#include "switch.h"
#include <iostream>
Switch::Switch(int row, int col) : Tile(row, col)
{
}

string Switch::getTexture()
{
    if (character != nullptr)
        return "x";
    else
        return "?";
}

Tile *Switch::onEnter(Tile *fromTile, Character *who)
{
    if(who)
        this->activate();
    return this;
}

Tile *Switch::onLeave(Tile *destTile, Character *who)
{
    return this;
}

void Switch::attach(Passive *p)
{
    for (size_t i = 0; i < passiveList.size(); i++)
    {
        if (p == passiveList.at(i))
            return;
    }
    passiveList.push_back(p);
}

void Switch::detach(Passive *p)
{
    for (size_t i = 0; i < passiveList.size(); i++)
    {
        if (p == passiveList.at(i))
            passiveList.erase(passiveList.begin() + i);
    }
}

void Switch::activate()
{
    for (size_t i = 0; i < passiveList.size(); i++)
    {
        passiveList.at(i)->notify(this);
    }
}

int Switch::getPassiveSize() const
{
    return this->passiveList.size();
}

const std::vector<Passive *> &Switch::getPassiveList() const
{
    return this->passiveList;
}

