#ifndef FLOOR_H
#define FLOOR_H
#include "tile.h"

class Floor : public Tile
{
public:
    Floor(int row, int col);

    // Tile interface
public:
    string getTexture() override;

    Tile *onEnter(Tile *fromTile, Character *who) override;

    // Tile interface
public:
    Tile *onLeave(Tile *destTile, Character *who) override;
};

#endif // FLOOR_H
