#include "dungeoncrawler.h"
#include "terminalui.h"
#include <iostream>

#include "graphicalui.h"
#include "levelchanger.h"
#include <QApplication>
#include <QLabel>

#include "guardcontroller.h"
#include "stationarycontroller.h"
#include "controller.h"

#include "lootchest.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GraphicalUI *gui = new GraphicalUI;
    Level *l = new Level(gui, 0);
    Level *level2 = new Level(gui, 2);

    level2->field.at(3).at(3) = new Lootchest(3, 3, gui);

    Character *char1 = new Character("x", 1, l->getController(),50, 500, true);
    l->characters.push_back(char1);
    char1->setTile(l->getTile(2, 2));
    char1->getTile()->setCharacter(char1);

    string muster = "66444466";
    GuardController *g = new GuardController(muster);
    Character *zombie = new Character("x", 1, g);
    l->getTile(5, 3)->setCharacter(zombie);
    zombie->setTile(l->getTile(5, 3));
    l->getCharacters().push_back(zombie);

    StationaryController *sc = new StationaryController;
    Character *zombie2 = new Character("x", 1, sc, 100, 100, false);
    l->getTile(0, 4)->setCharacter(zombie2);
    zombie2->setTile(l->getTile(0, 4));
    l->getCharacters().push_back(zombie2);

    LevelChanger *leveChanger1 = new LevelChanger(level2, nullptr, 3, 3);
    delete l->field.at(3).at(3);
    l->field.at(3).at(3) = leveChanger1;

    LevelChanger *leveChanger2 = new LevelChanger(l, nullptr, 0, 4);
    delete level2->field.at(0).at(4);
    level2->field.at(0).at(4) = leveChanger2;

    DungeonCrawler dungeon(gui, l);

    dungeon.addLevel(l);
    dungeon.addLevel(level2);

    leveChanger1->attach(&dungeon);
    leveChanger2->attach(&dungeon);
    leveChanger1->setDestTile(leveChanger2);
    leveChanger2->setDestTile(leveChanger1);

    l->getPath(char1->getTile(),zombie2->getTile());
   Graph::Knoten* n =  (l->getGraph()->findKnoten(2,2));
   if(0==0){
       std:: cout << "row gefunden";
   }
    dungeon.play();
    app.exec();

}
