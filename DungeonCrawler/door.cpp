#include "door.h"
#include "active.h"
#include <iostream>
Door::Door(int row, int col) : Tile(row, col)
{
    open = false;
}

void Door::notify(Active *source)
{
    open = !open;
}

string Door::getTexture()
{
    if (open == true)
        return "/";
    else
        return "X";
}

Tile *Door::onEnter(Tile *fromTile, Character *who)
{
    if (open == true)
        return this;
    else
        return nullptr;
}

Tile *Door::onLeave(Tile *destTile, Character *who)
{
    if(who or open)
        return this;
    else
        return nullptr;
}

bool Door::getOpen() const
{
    return open;
}

void Door::setOpen(bool newOpen)
{
    open = newOpen;
}
