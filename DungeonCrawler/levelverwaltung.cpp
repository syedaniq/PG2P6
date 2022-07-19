#include "levelverwaltung.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include "graph.h"

#include "controller.h"
#include "stationarycontroller.h"
#include "guardcontroller.h"
#include "attackcontroller.h"

#include "levelchanger.h"
#include "wall.h"
#include "floor.h"
#include "ramp.h"
#include "switch.h"
#include "lootchest.h"
#include "pit.h"
#include "portal.h"
#include "door.h"


Levelverwaltung::Levelverwaltung()
{
}

void Levelverwaltung::einlesen(std::string& dateiname)
{
    ifstream quelle(dateiname.c_str(), ios::in);

     if (!quelle.good())
     {
       cerr << dateiname << " kann nicht geoeffnet werden!\n";
       exit(-1);
     }

         json jFile;
         quelle >> jFile;
         Level* l;

        for(const auto& item: jFile.items())
        {
           if(item.key()=="_level")
           {
               int row, col;
               for(const auto& valueItem: item.value().items())
               {
                   if(valueItem.key()=="cols")
                      col = valueItem.value();
                   if(valueItem.key()=="rows")
                       row = valueItem.value();
               }
               l = new Level( row, col );
           }

        }

        for(const auto& item: jFile["characters"])
        {
            int hp, row, col, stamina, strength;
            string controllerName;
            bool isHuman;
            Controller* controller;

            for(auto& values : item.items())
            {

                if(values.key() == "hp")
                    hp = values.value();
                if(values.key() == "row")
                    row = values.value();
                if(values.key() == "col")
                    col = values.value();
                if(values.key() == "stamina")
                    stamina = values.value();
                if(values.key() == "strength")
                    strength = values.value();
                if(values.key() == "texture")
                {
                    if(values.value() == "hero")
                        isHuman = true;
                    else
                        isHuman = false;
                }
                if(values.key() == "controller")
                {
                    cout << endl;
                    cout << "Hi" << endl;
                    cout << endl;
                    for(auto& iwas : values.value().items())
                    {
                        if(iwas.key() == "name")
                        {
                            if(iwas.value() == "stationarycontroller")
                                controller = new StationaryController;
                            if(iwas.value() == "uicontroller")
                                controller = l->getController();
                            if(iwas.value() == "attackcontroller")
                                controller = new AttackController(l);
                        }
                        if(iwas.key() == "movement")
                        {
                            string muster = iwas.value();
                            controller = new GuardController(muster);
                        }
                    }
                }

            }
            Character* c = new Character("x",1,controller,strength,stamina,isHuman);
            l->getCharacters().push_back(c);
            cout << "END OF FILE" << endl;
        }
        int portalindex=0;
        int portalpair=0;
        for(const auto& item: jFile["tiles"])
        {
            Tile* tile;
            string typ="";
            int row=0;
            int col=0;
            int destrow=0;
            int destcol=0;
            for(const auto& values: item.items())
            {
                if(values.key()=="row")
                    row = values.value();
                if(values.key()=="col")
                    col=values.value();
                if(values.key()=="name")
                    typ = values.value();
                if(values.key()=="destrow")
                    destrow=values.value();
                if(values.key()=="destcol")
                    destcol=values.value();
            }

            if(typ=="wall")
               tile = new Wall(row,col);
            if(typ=="door")
                tile = new Door(row,col);
            if(typ=="floor")
                tile= new Floor(row,col);
            if(typ =="treasure")
                tile = new Lootchest(row,col, nullptr);
            if(typ=="pit")
                tile = new Pit(row,col);
            if(typ=="portal"){
                portalpair++;
                tile= new Portal(row, col, l->getTile(destrow,destcol), portalindex);
                if(portalpair==2){
                    portalpair=0;
                    portalindex++;
                }
            }
            if(typ=="ramp")
                tile= new Ramp(col,row);
            if(typ =="switch")
                tile = new Switch(row, col);

            l->getField().at(row).at(col)= tile;
        }
         quelle.close();
}


void Levelverwaltung::einspeichern(Level *level)
{
    json j;
    j["_level"]["cols"] = level->getCOL();
    string name = "level";
    name.append(to_string(level->getCOL()/level->getROW()));
    j["_level"]["name"] = name;
    j["_level"]["rows"] = level->getROW();

    j["characters"] = json::array();

    for(int i=0; i<level->getCharacters().size(); i++)
    {
        string texture;
        if(level->getCharacters().at(i)->getIsHuman())
            texture = "hero";
        else
            texture = "goblin";

        json jController;

        if(typeid(*level->getCharacters().at(i)->getController()) == typeid(GuardController))
        {
            GuardController* gc = dynamic_cast<GuardController*>(level->getCharacters().at(i)->getController());
            jController["movement"] = gc->getMuster();
            jController["name"] = "guardcontroller";
        }
        else if(typeid(*level->getCharacters().at(i)->getController()) == typeid(StationaryController))
            jController["name"] = "stationarycontroller";
        else if(typeid(*level->getCharacters().at(i)->getController()) == typeid(AttackController))
            jController["name"] = "attackcontroller";
        else
            jController["name"] = "uicontroller";

        j["characters"].push_back({{"col", level->getCharacters().at(i)->getTile()->getCol()},
                                   {"controller", jController},
                                   {"hp", level->getCharacters().at(i)->getHitpoints()},
                                   {"row", level->getCharacters().at(i)->getTile()->getRow()},
                                   {"stamina", level->getCharacters().at(i)->getStamina()},
                                   {"strength", level->getCharacters().at(i)->getStrength()},
                                   {"texture", texture}
                                  });
    }

    j["tiles"] = json::array();

    for(int a=0; a<level->getROW(); a++)
    {
        for(int b=0; b<level->getCOL(); b++)
        {
            string tileName;
            if(typeid(*level->getTile(a,b)) == typeid(Floor))
                tileName = "floor";
            else if(typeid(*level->getTile(a,b)) == typeid(Wall))
                tileName = "wall";
            else if(typeid(*level->getTile(a,b)) == typeid(Pit))
                tileName = "pit";
            else if(typeid(*level->getTile(a,b)) == typeid(Ramp))
                tileName = "ramp";
            else if(typeid(*level->getTile(a,b)) == typeid(Door))
            {
                tileName = "door";
                Door* d = dynamic_cast<Door*>(level->getTile(a,b));
                j["tiles"].push_back({{"col", level->getTile(a,b)->getCol()},
                                      {"is_open", d->getOpen()},
                                      {"name", tileName},
                                      {"row", level->getTile(a,b)->getRow()},
                                      {"texture", tileName}
                                     });
                continue;
            }
            else if(typeid(*level->getTile(a,b)) == typeid(Portal))
            {
                tileName = "portal";
                Portal* d = dynamic_cast<Portal*>(level->getTile(a,b));
                j["tiles"].push_back({{"col", level->getTile(a,b)->getCol()},
                                      {"destcol", d->getDestination()->getCol()},
                                      {"destrow", d->getDestination()->getRow()},
                                      {"name", tileName},
                                      {"row", level->getTile(a,b)->getRow()},
                                      {"texture", tileName}
                                     });
                continue;
            }
            else if(typeid(*level->getTile(a,b)) == typeid(LevelChanger))
            {
                tileName = "levelchanger";
                LevelChanger* d = dynamic_cast<LevelChanger*>(level->getTile(a,b));
                j["tiles"].push_back({{"col", level->getTile(a,b)->getCol()},
                                      {"destcol", d->getDestTile()->getCol()},
                                      {"destrow", d->getDestTile()->getRow()},
                                      {"name", tileName},
                                      {"row", level->getTile(a,b)->getRow()},
                                      {"targetLevelID", d->getToLevel()->getId()},
                                      {"texture", tileName}
                                     });
                continue;
            }
            else if(typeid(*level->getTile(a,b)) == typeid(Switch))
            {
                tileName = "switch";
                Switch* d = dynamic_cast<Switch*>(level->getTile(a,b));
                json targets;
                j["ztargets"] = json::array();

                for(auto& tiles : d->getPassiveList())
                {
                    Tile* t = dynamic_cast<Tile*>(tiles);
                    targets["col"] = t->getCol();
                    targets["row"] = t->getRow();
                    targets["type"] = "door";
                    j["ztargets"].push_back(targets);
                }
                j["tiles"].push_back({{"col", level->getTile(a,b)->getCol()},
                                      {"name", tileName},
                                      {"row", level->getTile(a,b)->getRow()},
                                      {"targets", j["ztargets"]},
                                      {"texture", tileName}
                                     });

                j.erase("ztargets");
                continue;
            }
            j["tiles"].push_back({{"col", level->getTile(a,b)->getCol()},
                                  {"name", tileName},
                                  {"row", level->getTile(a,b)->getRow()},
                                  {"texture", tileName}
                                 });
        }
    }

    ofstream outfile("backup.json");
    outfile << j.dump(2);
}
