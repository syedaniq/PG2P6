#ifndef STATIONARYCONTROLLER_H
#define STATIONARYCONTROLLER_H

#include "controller.h"

class StationaryController : public Controller
{
public:
    StationaryController();

    // Controller interface
public:
    int move();
};

#endif // STATIONARYCONTROLLER_H
