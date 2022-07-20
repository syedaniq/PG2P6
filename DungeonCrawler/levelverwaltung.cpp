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

Level *Levelverwaltung::einlesen(string &dateiname, GraphicalUI *gui, DungeonCrawler* dungeon)
{
    this->dungeon = dungeon;

    ifstream quelle(dateiname.c_str(), ios::in);
    vector<charPos*>characters;
    vector<switchTarget>switchs;
    vector<portalConnect>portale;

     if (!quelle.good())
     {
       cerr << dateiname << " kann nicht geoeffnet werden!\n";
       exit(-1);
     }

     json jFile;
     quelle >> jFile;
     Level* level;
     quelle.close();

     for(const auto& item: jFile.items())
     {
        if(item.key()=="_level")
        {
            int row, col, id;
            for(const auto& valueItem: item.value().items())
            {
                if(valueItem.key()=="cols")
                   col = valueItem.value();
                if(valueItem.key()=="rows")
                    row = valueItem.value();
                if(valueItem.key()=="id")
                    id = valueItem.value();
            }
            level = new Level(gui,row,col, id);
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
                 for(auto& iwas : values.value().items())
                 {
                     if(iwas.key() == "name")
                     {
                         if(iwas.value() == "stationarycontroller")
                             controller = new StationaryController;
                         if(iwas.value() == "uicontroller")
                             controller = level->getController();
                         if(iwas.value() == "attackcontroller")
                             controller = new AttackController(level);
                     }
                     if(iwas.key() == "movement")
                     {
                         string muster = iwas.value();
                         controller = new GuardController(muster);
                     }
                 }
             }
         }
            charPos* cP = new charPos;
            Character* c = new Character("x",1,controller,strength,stamina,isHuman);
            cP->character = c;
            cP->col = col;
            cP->row = row;
            characters.push_back(cP);
        }

        for(const auto& item: jFile["tiles"])
        {
            Tile* tile;
            string typ="";
            int row=0;
            int col=0;
            int destrow=0;
            int destcol=0;
            int id = 0, portalType = 0,destLevelIndex = 0;
            bool is_open = 0;

            for(const auto& values: item.items())
            {
                if(values.key()=="row")
                    row = values.value();
                else if(values.key()=="col")
                    col=values.value();
                else if(values.key()=="name")
                    typ = values.value();
                else if(values.key()=="destrow")
                    destrow=values.value();
                else if(values.key()=="destcol")
                    destcol=values.value();
                else if(values.key()=="id")
                    id=values.value();
                else if(values.key()=="is_open")
                    is_open=values.value();
                else if(values.key() == "portalType")
                    portalType=values.value();
                else if(values.key() == "destLevelIndex")
                    destLevelIndex=values.value();
                else if(values.key()=="targets")
                {
                    for(auto& kA : values.value().items())
                    {
                        for(auto& egal : kA.value().items()) {
                            if(egal.key()=="row")
                                destrow = egal.value();
                            if(egal.key()=="col")
                                destcol = egal.value();
                        }
                    }
                }
                else
                    continue;
            }

            if(typ=="wall")
               tile = new Wall(row,col);
            if(typ=="door")
                tile = new Door(row,col);
            if(typ=="floor")
                tile= new Floor(row,col);
            if(typ =="treasure") {
                tile = new Lootchest(row,col,gui);
                Lootchest* lc = dynamic_cast<Lootchest*>(tile);
                lc->setG(gui);
                level->getField().at(row).at(col)=lc;
                continue;
            }
            if(typ=="pit")
                tile = new Pit(row,col);
            if(typ=="portal"){
                portalConnect pC;
                pC.source = new Portal(row, col, nullptr, portalType);
                pC.targetCol = destcol;
                pC.targetRow = destrow;
                tile = pC.source;
                portale.push_back(pC);
            }
            if(typ=="ramp")
                tile= new Ramp(row,col);
            if(typ =="switch") {
                switchTarget sT;
                sT.sourceCol = col;
                sT.sourceRow = row;
                sT.targetCol = destcol;
                sT.targetRow = destrow;
                switchs.push_back(sT);
                tile = new Switch(row, col);
            }
            if(typ == "levelchanger")
            {
                tile = new LevelChanger(row,col,id,destLevelIndex);
                LevelChanger* lc = dynamic_cast<LevelChanger*>(tile);
                lc->attach(dungeon);
            }
            level->getField().at(row).at(col)= tile;
        }

        for(auto& chars : characters)
        {
            level->placeCharacter(chars->character,chars->row,chars->col);
        }

        for(auto& portale : portale)
        {
            portale.source->setDestination(level->getTile(portale.targetRow,portale.targetCol));
        }

        for(auto& switches : switchs)
        {
            Switch* s = dynamic_cast<Switch*>(level->getTile(switches.sourceRow,switches.sourceCol));
            Door* d = dynamic_cast<Door*>(level->getTile(switches.targetRow,switches.targetCol));
            s->attach(d);
        }

        return level;
}


void Levelverwaltung::einspeichern(Level *level, int index)
{
    json j;
    j["_level"]["cols"] = level->getCOL();
    string name = "level";
    name.append(to_string(level->getCOL()/level->getROW()));
    j["_level"]["id"] = level->getId();
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
                                      {"texture", tileName},
                                      {"portalType", d->getPortalType()}
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
                                      {"texture", tileName},
                                      {"destLevelIndex", d->getDestLevelIndex()},
                                      {"id", d->getId()}
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


    string pfad = "backup";
    pfad.append(to_string(index));
    pfad.append(".json");

    ofstream outfile(pfad);
    outfile << j.dump(2);
}
