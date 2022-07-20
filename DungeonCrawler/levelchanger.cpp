#include "levelchanger.h"

LevelChanger::LevelChanger(int row, int col, int id, int destLevelIndex)
    : Tile(row,col), id(id), destLevelIndex(destLevelIndex)
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

    if (!who)
        return nullptr;

    for (int i = 0; i< toLevel->getROW(); i++)
    {
        for (int j = 0; j < toLevel->getCOL(); j++)
        {
            Tile* tmp = toLevel->getTile(i, j);
            if (typeid(*tmp) == typeid(LevelChanger))
            {
                LevelChanger* destLevelChanger = dynamic_cast<LevelChanger*>(tmp);
                if (destLevelChanger->getId() == this->getId())
                {
                    destTile = tmp;
                    activate();
                    return tmp;
                }
            }
        }
    }
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

int LevelChanger::getDestLevelIndex() const
{
    return destLevelIndex;
}

void LevelChanger::setDestLevelIndex(int value)
{
    destLevelIndex = value;
}

int LevelChanger::getId() const
{
    return id;
}

void LevelChanger::setId(int value)
{
    id = value;
}
