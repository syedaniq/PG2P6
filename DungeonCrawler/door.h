#ifndef DOOR_H
#define DOOR_H
#include "passive.h"
#include "tile.h"

class Door : public Tile, public Passive
{
public:
    Door(int row, int col);

    // Passive interface
public:
    void notify(Active *source) override;

    // Tile interface
public:
    string getTexture() override;
    Tile *onEnter(Tile *fromTile, Character *who) override;
    Tile *onLeave(Tile *destTile, Character *who) override;

    bool getOpen() const;

    void setOpen(bool newOpen);

private:
    bool open;
    int counter = 0;
};

#endif // DOOR_H
