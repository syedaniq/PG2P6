#ifndef LEVELCHANGER_H
#define LEVELCHANGER_H

#include "active.h"
#include "level.h"
#include "tile.h"

class LevelChanger : public Tile, public Active
{
public:
    LevelChanger(Level *toLevel, Tile *destTile, int row, int col);

    // Active interface
public:
    void attach(Passive *p);
    void detach(Passive *p);
    void activate();

    // Tile interface
public:
    string getTexture();
    Tile *onEnter(Tile *fromTile, Character *who);
    Tile *onLeave(Tile *destTile, Character *who);

    Level *getToLevel() const;
    void setToLevel(Level *newToLevel);
    Tile *getDestTile() const;
    void setDestTile(Tile *newDestTile);

private:
    Level *toLevel;
    Tile *destTile;
};

#endif // LEVELCHANGER_H
