#include "levelchanger.h"

LevelChanger::LevelChanger(Level *toLevel, Tile *destTile, int row, int col)
    : Tile(row, col), toLevel(toLevel), destTile(destTile)
{
    this->texture = "L";
    this->character = nullptr;
}

void LevelChanger::attach(Passive *p)
{
    for (size_t i = 0; i < passiveList.size(); i++)
    {
        if (p == passiveList.at(i))
            return;
    }
    passiveList.push_back(p);
}

void LevelChanger::detach(Passive *p)
{
    for (size_t i = 0; i < passiveList.size(); i++)
    {
        if (p == passiveList.at(i))
            passiveList.erase(passiveList.begin() + i);
    }
}

void LevelChanger::activate()
{
    for (size_t i = 0; i < passiveList.size(); i++)
    {
        passiveList.at(i)->notify(this);
    }
}

string LevelChanger::getTexture()
{
    if (character != nullptr)
        return "x";
    else
        return "L";
}

Tile *LevelChanger::onEnter(Tile *fromTile, Character *who)
{
    if(who) {
        activate();
        return destTile;
    } else
        return nullptr;
}

Tile *LevelChanger::onLeave(Tile *destTile, Character *who)
{
    return this;
}

Level *LevelChanger::getToLevel() const
{
    return toLevel;
}

void LevelChanger::setToLevel(Level *newToLevel)
{
    toLevel = newToLevel;
}

Tile *LevelChanger::getDestTile() const
{
    return destTile;
}

void LevelChanger::setDestTile(Tile *newDestTile)
{
    destTile = newDestTile;
}
