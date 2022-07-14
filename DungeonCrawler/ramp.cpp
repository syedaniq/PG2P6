#include "ramp.h"

Ramp::Ramp(int row, int col) : Tile(row, col)
{
}

string Ramp::getTexture()
{
    if (character != nullptr)
        return "x";
    else
        return ">";
}

Tile *Ramp::onEnter(Tile *fromTile, Character *who)
{
    return this;
}

Tile *Ramp::onLeave(Tile *destTile, Character *who)
{
    return this;
}
