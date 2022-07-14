#include "tile.h"
#include <typeinfo>
#include <iostream>
Tile::Tile(int row, int col) : row(row), col(col)
{
}

bool Tile::moveTo(Tile *destTile, Character *who)
{
    Tile* fromTile(onLeave(destTile,who));

    if(!fromTile)
        return false;

    Tile* toTile(destTile->onEnter(fromTile,who));

    if(!toTile)
        return false;

    Character *enemy = toTile->character;

    if(enemy)
    {
        if(who->getIsHuman() != enemy->getIsHuman())
        {
            who->fight(enemy);
            if(enemy->getHitpoints() > 0)
            {
                enemy->fight(who);
            }
            if(enemy->getHitpoints() > 0)
            {
                return false;
            }
        }
        else
            return false;
    }

    Tile::character = nullptr;
    toTile->setCharacter(who);
    who->setTile(toTile);

    return true;
}



void Tile::setTexture(const string& newTexture)
{
    texture = newTexture;
}

Character* Tile::getCharacter() const
{
    return character;
}

void Tile::setCharacter(Character* newCharacter)
{
    character = newCharacter;
}

int Tile::getRow() const
{
    return row;
}

int Tile::getCol() const
{
    return col;
}

bool Tile::hasCharacter()
{
    if (character == nullptr)
        return false;
    else
        return true;
}

bool Tile::getCharacterDied() const
{
    return characterDied;
}

void Tile::setCharacterDied(bool value)
{
    characterDied = value;
}
