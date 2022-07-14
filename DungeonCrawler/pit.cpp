#include "pit.h"

Pit::Pit(int row, int col) : Tile(row, col)
{
}

string Pit::getTexture()
{
    if (character != nullptr)
        return "x";
    else
        return "_";
}

Tile *Pit::onEnter(Tile *fromTile, Character *who)
{
    return this;
}

Tile *Pit::onLeave(Tile *destTile, Character *who)
{
    if ((destTile->getTexture() == "_") or (destTile->getTexture() == ">"))
        return this;
    else
        return nullptr;
}
