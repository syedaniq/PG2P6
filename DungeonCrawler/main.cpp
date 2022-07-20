#include "dungeoncrawler.h"
#include "terminalui.h"
#include <iostream>

#include "graphicalui.h"
#include "levelchanger.h"
#include <QApplication>
#include <QLabel>

#include "guardcontroller.h"
#include "stationarycontroller.h"
#include "attackcontroller.h"
#include "controller.h"

#include "lootchest.h"
#include "levelverwaltung.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[])
{

    /*Level *l = new Level(gui, 0);
    Level *level2 = new Level(gui, 2);

    level2->field.at(3).at(3) = new Lootchest(3, 3, gui);

    Character *char1 = new Character("x", 1, l->getController(),50, 500, true);
    l->characters.push_back(char1);
    l->placeCharacter(char1,4,2);*/

    /*string muster = "66444466";
    GuardController *g = new GuardController(muster);
    Character *zombie = new Character("x", 1, g);
    l->getTile(5, 3)->setCharacter(zombie);
    zombie->setTile(l->getTile(5, 3));
    l->getCharacters().push_back(zombie);

    StationaryController *sc = new StationaryController;
    Character *zombie2 = new Character("x", 1, sc, 100, 100, false);
    l->getTile(0, 4)->setCharacter(zombie2);
    zombie2->setTile(l->getTile(0, 4));
    l->getCharacters().push_back(zombie2);*/

    /*AttackController *ac = new AttackController(l);
    Character* zombie3 = new Character("x",1,ac);
    l->getTile(0,5)->setCharacter(zombie3);
    zombie3->setTile(l->getTile(0,5));
    l->getCharacters().push_back(zombie3);

    LevelChanger *leveChanger1 = new LevelChanger(level2, nullptr, 3, 3);
    delete l->field.at(3).at(3);
    l->field.at(3).at(3) = leveChanger1;
    l->getGraph()->update();
    LevelChanger *leveChanger2 = new LevelChanger(l, nullptr, 0, 4);
    delete level2->field.at(0).at(4);
    level2->field.at(0).at(4) = leveChanger2;


    dungeon.addLevel(level2);

    leveChanger1->attach(&dungeon);
    leveChanger2->attach(&dungeon);
    leveChanger1->setDestTile(leveChanger2);
    leveChanger2->setDestTile(leveChanger1);*/
 char eingabe;
    cout << "Spielstand Laden?- Geben Sie L ein für Level Laden oder N für neues Spiel: ";
            cin >> eingabe;
    if(eingabe =='L'){
        QApplication app(argc, argv);
        GraphicalUI *gui = new GraphicalUI;
    DungeonCrawler* dungeon = new DungeonCrawler(gui);
    string s="backup0.json";
    Levelverwaltung *lv = new Levelverwaltung;
    //lv->einspeichern(l);
    Level* l = lv->einlesen(s,gui,dungeon);
    Graph* graph = new Graph(l);
    l->setGraph(graph);
    dungeon->addLevel(l);
    dungeon->setLevel(l);
    s="backup1.json";

    l = lv->einlesen(s,nullptr,dungeon);
    graph = new Graph(l);
    l->setGraph(graph);
    dungeon->addLevel(l);

    dungeon->play();
    app.exec();
    }
            if(eingabe='N'){
                QApplication app(argc, argv);
                GraphicalUI *gui = new GraphicalUI;
                DungeonCrawler* dungeon = new DungeonCrawler(gui);
                string s=":/level1.json";
                Levelverwaltung *lv = new Levelverwaltung;
                //lv->einspeichern(l);
                Level* l = lv->einlesen(s,gui,dungeon);
                Graph* graph = new Graph(l);
                l->setGraph(graph);
                dungeon->addLevel(l);
                dungeon->setLevel(l);
                s=":/level2.json";

                l = lv->einlesen(s,nullptr,dungeon);
                graph = new Graph(l);
                l->setGraph(graph);
                dungeon->addLevel(l);

                dungeon->play();
                app.exec();
            }
}
