#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H

#include "controller.h"
#include "level.h"

class AttackController : public Controller
{
public:
    AttackController(Level* level);

    // Controller interface
public:
    int move();
private:
    int index = 0, iterator = 0;
    Level* level;
    vector<int>rueckgabe;
    void convertPath();
    int getMoveInt(Tile* from, Tile* to);
};

#endif // ATTACKCONTROLLER_H
