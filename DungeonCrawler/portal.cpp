#include "portal.h"

Portal::Portal(int row, int col, Tile *destination, int portalType) : Tile(row, col), destination(destination), portalType(portalType)
{
    this->texture = "O";
    this->character = nullptr;
}

Tile *Portal::getDestination() const
{
    return destination;
}

int Portal::getPortalType() const
{
    return portalType;
}

void Portal::setDestination(Tile *newDestination)
{
    destination = newDestination;
}

string Portal::getTexture()
{
    if (character != nullptr)
        return "x";
    else
        return "O";
}

Tile *Portal::onEnter(Tile * /*fromTile*/, Character * /*who*/)
{
    return this->getDestination();
}

Tile *Portal::onLeave(Tile * /*destTile*/, Character * /*who*/)
{
    return this;
}
