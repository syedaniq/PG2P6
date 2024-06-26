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

    char eingabe;

    do {
        cout << "---- Spielstand Laden? ----" << endl;
        cout << "- ja -> y" << endl;
        cout << "- nein -> n" << endl;
        cout << "- abbrechen -> q" << endl;
        cout << endl;
        cout << "Eingabe: ";
        cin >> eingabe;

        if(eingabe =='y')
        {
            QApplication app(argc, argv);
            GraphicalUI *gui = new GraphicalUI;
            DungeonCrawler* dungeon = new DungeonCrawler(gui);
            string s="/home/aniq/Documents/PG2P6/build-DungeonCrawler-Desktop_Qt_6_3_0_GCC_64bit-Debug/backup0.json";
            Levelverwaltung *lv = new Levelverwaltung;

            Level* l = lv->einlesen(s,gui,dungeon);
            Graph* graph = new Graph(l);
            l->setGraph(graph);
            dungeon->addLevel(l);
            dungeon->setLevel(l);
            s="/home/aniq/Documents/PG2P6/build-DungeonCrawler-Desktop_Qt_6_3_0_GCC_64bit-Debug/backup1.json";

            l = lv->einlesen(s,nullptr,dungeon);
            graph = new Graph(l);
            l->setGraph(graph);
            dungeon->addLevel(l);

            dungeon->play();
            app.exec();
        }
        else if(eingabe=='n')
        {
            QApplication app(argc, argv);
            GraphicalUI *gui = new GraphicalUI;
            DungeonCrawler* dungeon = new DungeonCrawler(gui);
            string s="/home/aniq/Documents/PG2P6/DungeonCrawler/level1.json";
            Levelverwaltung *lv = new Levelverwaltung;
            //lv->einspeichern(l);
            Level* l = lv->einlesen(s,gui,dungeon);
            Graph* graph = new Graph(l);
            l->setGraph(graph);
            dungeon->addLevel(l);
            dungeon->setLevel(l);
            s="/home/aniq/Documents/PG2P6/DungeonCrawler/level2.json";

            l = lv->einlesen(s,nullptr,dungeon);
            graph = new Graph(l);
            l->setGraph(graph);
            dungeon->addLevel(l);

            dungeon->play();
            app.exec();
        }
        else {
            cout << "Ungueltige Eingabe!" << endl;
        }
    } while(eingabe != 'q');

}
