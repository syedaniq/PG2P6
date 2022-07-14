#ifndef CHARACTER_H
#define CHARACTER_H
#include "controller.h"
class Tile;
#include <string>
using std::string;

class Character
{
public:
    Character(string texture, int moveDirection, Controller *controller, int strength = 100, int stamina = 100, bool isHuman = false);
    ~Character(){};
    Tile *getTile() const;
    void setTile(Tile *newTile);
    const string &getTexture() const;
    int move();
    int getMaxHP();
    int getMoveDirection() const;
    void setMoveDirection(int value);

    int getHitpoints() const;
    void setHitpoints(int value);

    int getStrength() const;
    void setStrength(int value);

    int getStamina() const;
    void setStamina(int value);

    bool getIsHuman() const;
    void setIsHuman(bool value);

    Controller *getController() const;
    void setController(Controller *value);

    void fight(Character *enemy);

protected:
    Tile *tile;

private:
    bool isHuman;
    string texture;
    Controller *controller;
    int moveDirection;
    int strength, stamina, hitpoints;
};

#endif // CHARACTER_H
