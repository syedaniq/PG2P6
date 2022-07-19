#include "level.h"
#include "door.h"
#include "floor.h"
#include "levelchanger.h"
#include "pit.h"
#include "portal.h"
#include "ramp.h"
#include "switch.h"
#include "wall.h"
#include <iostream>
#include <typeinfo>

#include "attackcontroller.h"
#include <queue>
#include "guardcontroller.h"
Level::Level(Controller *controller, int x)
    :  ROW(6), COL(6), controller(controller), id(x)
{
    field.resize(ROW);
    Door *d = new Door(0, 0);
    Switch *s = new Switch(0, 2);
    Portal *p = new Portal(5, 5, nullptr, 2);
    Portal *p2 = new Portal(5, 0, p, 2);
    Ramp *r1 = new Ramp(5, 1);
    p->setDestination(p2);

    s->attach(d);

    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (i == 5 and j == 2)
                field.at(i).push_back(new Pit(i, j));
            else if (i == 5 and j == 1)
                field.at(i).push_back(r1);
            else if (i == 0 and j == 0)
                field.at(i).push_back(d);
            else if (i == 0 and j == 2)
                field.at(i).push_back(s);
            else if (i == 5 and j == 0)
                field.at(i).push_back(p2);
            else if (i == 5 and j == 5)
                field.at(i).push_back(p);
            else
                field.at(i).push_back(new Floor(i, j));
        }
    }

    Character *char1 = new Character("x", 1, this->getController(),50, 500, true);
    this->characters.push_back(char1);
    char1->setTile(this->getTile(4, 2));
    char1->getTile()->setCharacter(char1);

    string muster = "66444466";
    GuardController *g = new GuardController(muster);
    Character *zombie = new Character("x", 1, g);
    this->getTile(5, 3)->setCharacter(zombie);
    zombie->setTile(this->getTile(5, 3));
    this->getCharacters().push_back(zombie);

    graph = new Graph(this);
}

Level::Level(const Level &level) : ROW(level.ROW), COL(level.COL)
{
    cout << "operatorüberladung" << endl;

    field.resize(ROW);
    for (int i = 0; i < ROW; i++)
        field.at(i).resize(COL);

    for (size_t i = 0; i < level.field.size(); i++)
    {
        for (size_t j = 0; j < level.field.at(i).size(); j++)
        {
            if (typeid(field.at(i).at(j)) == typeid(Door))
            {
                Door *d = new Door(i, j);
                field.at(i).push_back(d);
            }
            else if (typeid(field.at(i).at(j)) == typeid(Floor))
            {
                Floor *l = new Floor(i, j);
                field.at(i).push_back(l);
            }
            else if (typeid(field.at(i).at(j)) == typeid(Pit))
            {
                Pit *l = new Pit(i, j);
                field.at(i).push_back(l);
            }
            else if (typeid(field.at(i).at(j)) == typeid(Portal))
            {
                Portal *p = dynamic_cast<Portal *>(field.at(i).at(j));
                Portal *l = new Portal(i, j, nullptr, p->getPortalType());
                field.at(i).push_back(l);
            }
            else if (typeid(field.at(i).at(j)) == typeid(Ramp))
            {
                Ramp *l = new Ramp(i, j);
                field.at(i).push_back(l);
            }
            else if (typeid(field.at(i).at(j)) == typeid(Switch))
            {
                Switch *l = new Switch(i, j);
                field.at(i).push_back(l);
            }
            else if (typeid(field.at(i).at(j)) == typeid(Wall))
            {
                Wall *l = new Wall(i, j);
                field.at(i).push_back(l);
            }
            else if (typeid(field.at(i).at(j)) == typeid(LevelChanger))
            {
                LevelChanger *oldlc = dynamic_cast<LevelChanger *>(field.at(i).at(j));
                LevelChanger *l = new LevelChanger(oldlc->getToLevel(), oldlc->getDestTile(), i, j);
                field.at(i).push_back(l);
            }
        }
    }

    for (size_t row = 0; row < field.size(); row++)
    {
        for (size_t col = 0; col < field.at(row).size(); col++)
        {
            if (level.field.at(row).at(col)->hasCharacter() and level.field.at(row).at(col)->getCharacter()->getHitpoints() > 0)
            {
                Character *c = level.field.at(row).at(col)->getCharacter();
                c->setMoveDirection(level.field.at(row).at(col)->getCharacter()->getMoveDirection());
                c->setStamina(level.field.at(row).at(col)->getCharacter()->getStamina());
                c->setStrength(level.field.at(row).at(col)->getCharacter()->getStrength());
                c->setHitpoints(level.field.at(row).at(col)->getCharacter()->getHitpoints());
                c->setController(level.field.at(row).at(col)->getCharacter()->getController());
                c->setIsHuman(level.field.at(row).at(col)->getCharacter()->getIsHuman());
                field.at(row).at(col)->setCharacter(c);
                characters.push_back(c);
            }
            if (typeid(field.at(row).at(col)) == typeid(Switch))
            {
                Switch *s = dynamic_cast<Switch *>(level.field.at(row).at(col));
                Switch *unserField;
                unserField = dynamic_cast<Switch *>(field.at(row).at(col));
                for (int i = 0; i < s->getPassiveSize(); i++)
                {

                    unserField->attach(s->getPassiveList().at(i));
                }
                field.at(row).at(col) = unserField;
            }
            if (typeid(field.at(row).at(col)) == typeid(Portal))
            {
                Portal *p = dynamic_cast<Portal *>(level.field.at(row).at(col));
                Portal *unserPortal =
                    dynamic_cast<Portal *>(field.at(row).at(col));
                unserPortal->setDestination(p->getDestination());
                field.at(row).at(col) = unserPortal;
            }
            if (typeid(field.at(row).at(col)) == typeid(LevelChanger))
            {
                LevelChanger *oldLC = dynamic_cast<LevelChanger *>(level.field.at(row).at(col));
                LevelChanger *lc = dynamic_cast<LevelChanger *>(field.at(row).at(col));
                lc->setDestTile(oldLC->getDestTile());
                lc->setToLevel(oldLC->getToLevel());
                field.at(row).at(col) = lc;
            }
        }
    }
}

Level::Level(int row, int col): ROW(row), COL(col)
{

}

int Level::getId() const
{
    return id;
}

Level::~Level()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            delete field.at(i).at(j);
        }
    }
    for (int i = 0; i < characters.size(); i++)
        delete characters.at(i);
}

Level &Level::operator=(const Level &level)
{
    cout << "operatorüberladung" << endl;

    field.resize(ROW);
    for (int i = 0; i < ROW; i++)
        field.at(i).resize(COL);

    for (size_t i = 0; i < level.field.size(); i++)
    {
        for (size_t j = 0; j < level.field.at(i).size(); j++)
        {
            if (typeid(field.at(i).at(j)) == typeid(Door))
            {
                Door *d = new Door(i, j);
                field.at(i).push_back(d);
            }
            else if (typeid(field.at(i).at(j)) == typeid(Floor))
            {
                Floor *l = new Floor(i, j);
                field.at(i).push_back(l);
            }
            else if (typeid(field.at(i).at(j)) == typeid(Pit))
            {
                Pit *l = new Pit(i, j);
                field.at(i).push_back(l);
            }
            else if (typeid(field.at(i).at(j)) == typeid(Portal))
            {
                Portal *p = dynamic_cast<Portal *>(field.at(i).at(j));
                Portal *l = new Portal(i, j, nullptr, p->getPortalType());
                field.at(i).push_back(l);
            }
            else if (typeid(field.at(i).at(j)) == typeid(Ramp))
            {
                Ramp *l = new Ramp(i, j);
                field.at(i).push_back(l);
            }
            else if (typeid(field.at(i).at(j)) == typeid(Switch))
            {
                Switch *l = new Switch(i, j);
                field.at(i).push_back(l);
            }
            else if (typeid(field.at(i).at(j)) == typeid(Wall))
            {
                Wall *l = new Wall(i, j);
                field.at(i).push_back(l);
            }
            else if (typeid(field.at(i).at(j)) == typeid(LevelChanger))
            {
                LevelChanger *l = new LevelChanger(nullptr, nullptr, i, j);
                field.at(i).push_back(l);
            }
        }
    }

    for (size_t row = 0; row < field.size(); row++)
    {
        for (size_t col = 0; col < field.at(row).size(); col++)
        {
            if (level.field.at(row).at(col)->hasCharacter())
            {
                Character *c = level.field.at(row).at(col)->getCharacter();
                c->setMoveDirection(level.field.at(row).at(col)->getCharacter()->getMoveDirection());
                c->setStamina(level.field.at(row).at(col)->getCharacter()->getStamina());
                c->setStrength(level.field.at(row).at(col)->getCharacter()->getStrength());
                c->setHitpoints(level.field.at(row).at(col)->getCharacter()->getHitpoints());
                c->setController(level.field.at(row).at(col)->getCharacter()->getController());
                c->setIsHuman(level.field.at(row).at(col)->getCharacter()->getIsHuman());
                field.at(row).at(col)->setCharacter(c);
                characters.push_back(c);
            }
            if (typeid(field.at(row).at(col)) == typeid(Switch))
            {

                Switch *s = dynamic_cast<Switch *>(level.field.at(row).at(col));
                Switch *unserField;
                unserField = dynamic_cast<Switch *>(field.at(row).at(col));
                for (int i = 0; i < s->getPassiveSize(); i++)
                {

                    unserField->attach(s->getPassiveList().at(i));
                }
                field.at(row).at(col) = unserField;
            }
            if (typeid(field.at(row).at(col)) == typeid(Portal))
            {
                Portal *p = dynamic_cast<Portal *>(level.field.at(row).at(col));
                Portal *unserPortal = dynamic_cast<Portal *>(field.at(row).at(col));
                unserPortal->setDestination(p->getDestination());
                field.at(row).at(col) = unserPortal;
            }
            if (typeid(field.at(row).at(col)) == typeid(LevelChanger))
            {
                LevelChanger *oldLC = dynamic_cast<LevelChanger *>(level.field.at(row).at(col));
                LevelChanger *lc = dynamic_cast<LevelChanger *>(field.at(row).at(col));
                lc->setDestTile(oldLC->getDestTile());
                lc->setToLevel(oldLC->getToLevel());
                field.at(row).at(col) = lc;
            }
        }
    }
}

Tile *Level::getTile(int row, int col)
{
    return field.at(row).at(col);
}

const Tile *Level::getTile(int row, int col) const
{
    return field.at(row).at(col);
}

void Level::placeCharacter(Character *c, int row, int col)
{
    field.at(row).at(col)->setCharacter(c);
}

vector<vector<Tile *>> &Level::getField()
{
    return field;
}

QVector<Character *> &Level::getCharacters()
{
    return characters;
}

int Level::getROW() const
{
    return ROW;
}

int Level::getCOL() const
{
    return COL;
}

Character* Level::getPlayer()
{
    for(auto& character : characters)
        if(character->getIsHuman())
            return character;

    return nullptr;
}

Character *Level::getGoblin()
{
    for(auto& character : characters)
        if(typeid(*character->getController()) == typeid(AttackController))
            return character;

    return nullptr;
}

void Level::removePlayer()
{
    characters.pop_front();
}

bool Level::removeDeadPlayers()
{
    for (int i = 0; i < characters.size(); i++)
    {
        if (characters.at(i)->getHitpoints() <= 0)
        {
            delete characters.at(i);
            characters.erase(characters.begin() + i);
            return true;
        }
    }
    return false;
}

void Level::addPlayer(Character *c)
{
    characters.push_front(c);
}

Controller *Level::getController() const
{
    return controller;
}

Graph *Level::getGraph() const
{
    return graph;
}

void Level::setGraph(Graph *value)
{
    graph = value;
}

vector<Tile*> Level::getPath(Tile *from, Tile *to)
{
    if(!ersterZug)
    {
        for(auto& knoten : graph->getKnoten())
        {
            knoten->besucht = false;
            knoten->parent = nullptr;
        }
    }

    ersterZug = false;
    Graph::Knoten* start = graph->findKnoten(from->getRow(),from->getCol());
    Graph::Knoten* ziel = graph->findKnoten(to->getRow(),to->getCol());

    queue<Graph::Knoten*>q;
    q.push(start);
    start->besucht = true;

    vector<Tile*> parents;

    if(!ziel)
    {
        parents.push_back(from);
        return parents;
    }

    while(!q.empty())
    {
        Graph::Knoten *u = q.front();
        u = graph->findKnoten(u->bezeichnung.row,u->bezeichnung.col);
        q.pop();

        for(auto& v : u->adjazenzliste)
        {
            v = graph->findKnoten(v->bezeichnung.row, v->bezeichnung.col);

            if(!v->besucht)
            {
                v->besucht = true;
                q.push(v);
                v->parent = u;
                //cout << "Nachbar in Queue gepusht: (" << v->bezeichnung.row << "/" << v->bezeichnung.col << ")"
                 //    << " Parent: (" << u->bezeichnung.row << "/" << u->bezeichnung.col << ")" << endl;

                if(v->bezeichnung.col == ziel->bezeichnung.col and v->bezeichnung.row == ziel->bezeichnung.row)
                {
                    auto current = v;
                    while(current != nullptr)
                    {
                        parents.push_back(this->getTile(current->bezeichnung.row,current->bezeichnung.col));
                        current = current->parent;
                    }

                    for(auto& parent : parents)
                        cout << "Parent: (" << parent->getRow() << "/" << parent->getCol() << ")" << endl;
                    return parents;
                }
            } else
            {
               // cout << "Bereits besucht: (" << v->bezeichnung.row << "/" << v->bezeichnung.col << ")" << endl;
            }
        }
    }
    return parents;
}
