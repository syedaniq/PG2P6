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
    Level* level;
};

#endif // ATTACKCONTROLLER_H
