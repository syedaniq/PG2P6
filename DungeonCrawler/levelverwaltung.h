#ifndef LEVELVERWALTUNG_H
#define LEVELVERWALTUNG_H

#include "json.hpp"
#include <string>
#include "level.h"
#include "graphicalui.h"
class Portal;
using namespace std;
using namespace nlohmann;

class Levelverwaltung
{
public:

    struct charPos {
        Character* character;
        int row;
        int col;
    };

    struct switchTarget {
        int sourceRow, sourceCol;
        int targetRow, targetCol;
    };

    struct portalConnect {
        Portal* source;
        int targetRow, targetCol;
    };

    Levelverwaltung();
    Level* einlesen(std::string& dateiname, GraphicalUI* gui);
    void einspeichern(Level* level);
};

#endif // LEVELVERWALTUNG_H
