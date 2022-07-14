#ifndef SWITCH_H
#define SWITCH_H
#include "tile.h"
#include "active.h"
class Switch : public Tile, public Active
{
public:
    Switch(int row, int col);

    // Tile interface
public:
    string getTexture() override;
    Tile *onEnter(Tile *fromTile, Character *who) override;
    Tile *onLeave(Tile *destTile, Character *who) override;

    // Active interface

public:
    void attach(Passive *p) override;
    void detach(Passive *p) override;
    void activate() override;
    int getPassiveSize()const;
    int test;

    // Active interface
public:
    const std::vector<Passive *>&getPassiveList() const override;
};

#endif // SWITCH_H
