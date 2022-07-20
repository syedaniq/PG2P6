#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H
#include "abstractui.h"
#include "terminalui.h"

#include "graphicalui.h"
#include "passive.h"
#include "list.h"

class DungeonCrawler : public Passive
{
public:
    DungeonCrawler(AbstractUI *abstractUI, Level *currentLevel);
    DungeonCrawler(AbstractUI* abstractUI);
    void play();
    void addLevel(Level *l);
    void setLevel(Level *l);

private:
    AbstractUI *abstractUI;
    Level *currentLevel;
    List levels;

    // Passive interface
public:
    void notify(Active *source);
};

#endif // DUNGEONCRAWLER_H
