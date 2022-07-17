#include "lootchest.h"
#include "graphicalui.h"
Lootchest::Lootchest(int row, int col, GraphicalUI *g) : Tile(row, col), g(g)
{
    this->texture = "C";
    this->character = nullptr;
}

string Lootchest::getTexture()
{
    if (character != nullptr)
        return "x";
    else
        return "C";
}

Tile *Lootchest::onEnter(Tile *fromTile, Character *who)
{
    if(!who or !fromTile)
        return  nullptr;

    if (who->getIsHuman())
    {
        g->hasWon();
    }
    return nullptr;
}

Tile *Lootchest::onLeave(Tile *destTile, Character *who)
{
    return this;
}
