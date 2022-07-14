#ifndef PORTAL_H
#define PORTAL_H
#include "tile.h"

class Portal : public Tile
{
public:
    Portal(int row, int col, Tile *destination, int portalType);
    Tile *getDestination() const;
    int getPortalType() const;

protected:
    Tile *destination;

private:
    int portalType;

    // Tile interface
public:
    string getTexture() override;
    Tile *onEnter(Tile *fromTile, Character *who) override;
    Tile *onLeave(Tile *destTile, Character *who) override;
    void setDestination(Tile *newDestination);
};

#endif // PORTAL_H
