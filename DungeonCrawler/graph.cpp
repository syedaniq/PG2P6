#include "graph.h"
#include "iostream"
#include <algorithm>
#include <array>
#include "portal.h"
#include "level.h"

std::vector<Knoten *> Graph::getKnoten() const
{
    return knoten;
}

Graph::Graph(Level *level) : level(level)
{
    for(int i=0; i<level->getROW(); i++)
    {
        for(int j=0; j<level->getCOL(); j++)
        {
            addKnoten(level->getTile(i,j));
        }
    }

    for(int i=0; i<level->getROW(); i++)
    {
        for(int j=0; j<level->getCOL(); j++)
        {
            addNachbarKanten(level->getTile(i,j));
        }
    }
}

void Graph::addKnoten(Tile *t)
{
    Knoten* n = new Knoten;
    n->bezeichnung.col = t->getCol();
    n->bezeichnung.row = t->getRow();

    if(find(knoten.begin(), knoten.end(), n) == knoten.end())
        knoten.push_back(n);
}

void Graph::addNachbarKanten(Tile* from)
{
    std::array<int,8> dr ={-1,1,0,0,-1,-1,1,1};
    std::array<int,8> dc ={0,0,1,-1,-1,1,1,-1};

    for(int i=0; i<8; i++)
    {
        int newRow = from->getRow() + dr.at(i);
        int newCol = from->getCol() + dc.at(i);

        if(newRow < 0 or newCol < 0)
            continue;
        if(newRow >= level->getROW() or newCol >= level->getCOL())
            continue;

        if(level->getTile(newRow,newCol)->onEnter(from,nullptr) and from->onLeave(level->getTile(newRow,newCol),nullptr))
        {
            if(level->getTile(newRow,newCol)->getTexture() == "O")
            {
                Portal* p = dynamic_cast<Portal*>(level->getTile(newRow,newCol));
                addKante(from,p->getDestination());
            }
            else
            {
                addKante(from,level->getTile(newRow,newCol));
            }
        }
    }
}

void Graph::addKante(Tile *from, Tile *to)
{
    Knoten* f = new Knoten;
    f->bezeichnung.col = from->getCol();
    f->bezeichnung.row = from->getRow();

    Knoten* t = new Knoten;
    t->bezeichnung.col = to->getCol();
    t->bezeichnung.row = to->getRow();

   for(size_t i=0; i<knoten.size(); i++)
    {
        if(knoten.at(i)->bezeichnung.col == from->getCol() and knoten.at(i)->bezeichnung.row == from->getRow())
        {
            for(size_t j=0; j<knoten.at(i)->adjazenzliste.size(); j++)
            {
                if(knoten.at(i)->adjazenzliste.at(j)->bezeichnung.col == to->getCol() and knoten.at(i)->adjazenzliste.at(j)->bezeichnung.row == to->getRow())
                    return;
            }
            knoten.at(i)->adjazenzliste.push_back(t);
        }
   }
}

void Graph::update()
{
    for(auto& knoten : knoten)
    {
        for(auto& adjazenz : knoten->adjazenzliste)
        {
            delete adjazenz;
        }
        knoten->adjazenzliste.clear();
        delete knoten;
    }
    knoten.clear();

    for(int i=0; i<level->getROW(); i++)
    {
        for(int j=0; j<level->getCOL(); j++)
        {
            addKnoten(level->getTile(i,j));
        }
    }

    for(int i=0; i<level->getROW(); i++)
    {
        for(int j=0; j<level->getCOL(); j++)
        {
            addNachbarKanten(level->getTile(i,j));
        }
    }
}

void Graph::print()
{
    for(auto& knoten : knoten)
    {
        cout << "Knoten: (" << knoten->bezeichnung.row << "/" << knoten->bezeichnung.col << ")";
        for(auto& adjazenzKnoten : knoten->adjazenzliste)
        {
            cout << " -> (" << adjazenzKnoten->bezeichnung.row << "/" << adjazenzKnoten->bezeichnung.col << ")";
        }
        cout << endl;
    }
}

std::vector<Knoten *> Knoten::getAdjazenzliste() const
{
    return adjazenzliste;
}
