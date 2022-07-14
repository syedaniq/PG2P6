#ifndef PIT_H
#define PIT_H
#include "tile.h"

class Pit : public Tile
{
public:
    Pit(int row, int col);

    // Tile interface
public:
    string getTexture();
    Tile *onEnter(Tile *fromTile, Character *who);
    Tile *onLeave(Tile *destTile, Character *who);
};

#endif // PIT_H
