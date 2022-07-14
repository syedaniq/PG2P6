#ifndef LOOTCHEST_H
#define LOOTCHEST_H

#include "tile.h"
class GraphicalUI;

class Lootchest : public Tile
{
public:
    Lootchest(int row, int col, GraphicalUI *g);
    // Tile interface
public:
    string getTexture();
    Tile *onEnter(Tile *fromTile, Character *who);
    Tile *onLeave(Tile *destTile, Character *who);

private:
    GraphicalUI *g;
};

#endif // LOOTCHEST_H
