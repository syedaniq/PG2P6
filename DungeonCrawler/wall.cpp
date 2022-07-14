#include "wall.h"

Wall::Wall(int row, int col) : Tile(row, col)
{
    this->texture = "#";
    this->character = nullptr;
}

string Wall::getTexture()
{
    if (character != nullptr)
        return "x";
    else
        return "#";
}

Tile *Wall::onEnter(Tile *fromTile, Character *who)
{
    return nullptr;
}

Tile *Wall::onLeave(Tile *destTile, Character *who)
{
    return nullptr;
}
