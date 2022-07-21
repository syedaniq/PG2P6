#ifndef LEVELVERWALTUNG_H
#define LEVELVERWALTUNG_H

#include "json.hpp"
#include <string>
#include "level.h"
#include "graphicalui.h"
#include "dungeoncrawler.h"
class Portal;
using namespace std;
using namespace nlohmann;

class Levelverwaltung
{
public:

    struct switchTarget {
        int sourceRow, sourceCol;
        int targetRow, targetCol;
    };

    struct portalConnect {
        Portal* source;
        int targetRow, targetCol;
    };

    Levelverwaltung();
    Level *einlesen(string &dateiname, GraphicalUI *gui, DungeonCrawler *dungeon);
    void einspeichern(Level *level, int index);

private:
    DungeonCrawler* dungeon;
};

#endif // LEVELVERWALTUNG_H
