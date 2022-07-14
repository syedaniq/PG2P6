#include "floor.h"

Floor::Floor(int row, int col) : Tile(row, col)
{
    this->texture = ".";
    this->character = nullptr;
}

string Floor::getTexture()
{
    if (character != nullptr)
        return "x";
    else
        return ".";
}

Tile *Floor::onEnter(Tile *fromTile, Character *who)
{
    return this;
}

Tile *Floor::onLeave(Tile *destTile, Character *who)
{
    return this;
}
