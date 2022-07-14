#ifndef TILE_H
#define TILE_H
#include <string>
#include "character.h"
class Floor;
using namespace std;

class Tile
{
public:
    Tile(int row, int col);
    virtual ~Tile(){};
    virtual string getTexture() = 0;
    bool moveTo(Tile *destTile, Character *who);
    virtual Tile *onEnter(Tile *fromTile, Character *who) = 0;
    virtual Tile *onLeave(Tile *destTile, Character *who) = 0;
    void setTexture(const string &newTexture);
    Character *getCharacter() const;
    void setCharacter(Character *newCharacter);
    int getRow() const;
    int getCol() const;
    bool hasCharacter();

    bool getCharacterDied() const;
    void setCharacterDied(bool value);

protected:
    string texture;
    Character *character = nullptr;
    const int row;
    const int col;

private:
    bool characterDied = false;
};

#endif // TILE_H
