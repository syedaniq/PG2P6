#ifndef WALL_H
#define WALL_H
#include "tile.h"

class Wall : public Tile
{
public:
    Wall(int row, int col);

    // Tile interface
public:
    string getTexture() override;
    Tile *onEnter(Tile *fromTile, Character *who) override;
    Tile *onLeave(Tile *destTile, Character *who) override;
};

#endif // WALL_H
