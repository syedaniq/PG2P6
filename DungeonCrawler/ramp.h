#ifndef RAMP_H
#define RAMP_H
#include "tile.h"

class Ramp : public Tile
{
public:
    Ramp(int row, int col);

    // Tile interface
public:
    string getTexture() override;
    Tile *onEnter(Tile *fromTile, Character *who) override;
    Tile *onLeave(Tile *destTile, Character *who) override;
};

#endif // RAMP_H
