#include "graph.h"
#include "iostream"
#include <algorithm>
#include <array>
#include "portal.h"
#include "level.h"

std::vector<Graph::Knoten *> Graph::getKnoten() const
{
    return knoten;
}

Graph::Graph(Level *level) : level(level)
{
    for(int i=0; i<level->getROW(); i++)
    {
        for(int j=0; j<level->getCOL(); j++)
        {
            if(level->getTile(i,j)->onEnter(nullptr,nullptr))
                if(level->getTile(i,j)->hasCharacter() and !level->getTile(i,j)->getCharacter()->getIsHuman())
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

Graph::~Graph()
{
    for(const auto& knoten:this->knoten )
    {
        for(const auto& nachbar: knoten->adjazenzliste)
        {

            delete nachbar;
        }
        knoten->getAdjazenzliste().clear();
        delete knoten;
    }
    knoten.clear();
    delete this->level;
}

void Graph::addKnoten(Tile *t)
{
    Knoten* n = new Knoten;
    n->bezeichnung.col = t->getCol();
    n->bezeichnung.row = t->getRow();

    if(find(knoten.begin(), knoten.end(), n) == knoten.end())
        knoten.push_back(n);
    delete n;
}

Graph::Knoten* Graph::findKnoten(int row, int col)
{
    int end = this->knoten.size()-1;
     int current =0;
    int begin=0;
    while(begin<=end)
    {
        current= (end+begin)/2;
        if(this->knoten.at(current)->bezeichnung.row==row)
        {
            if(this->knoten.at(current)->bezeichnung.col==col)
            {
                return knoten.at(current);
            }
            if(this->knoten.at(current)->bezeichnung.col<col)
            {
                 begin=current+1;
            }
            if(this->knoten.at(current)->bezeichnung.col>col)
            {
                end=current-1;
            }
        }
        else if(this->knoten.at(current)->bezeichnung.row<row)
        {
             begin=current+1;
        }
        else if(this->knoten.at(current)->bezeichnung.row>row)
        {
           end=current-1;
        }
        else if(begin==end)
        {
            return nullptr;
        }

    }
    return nullptr;
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
        if(level->getTile(newRow,newCol)->hasCharacter() and !level->getTile(newRow,newCol)->getCharacter()->getIsHuman())
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
   delete t;
   delete f;
}

void Graph::update()
{
    for(auto& knoten : knoten)
    {
        /*for(auto& adjazenz : knoten->adjazenzliste)
        {
            delete adjazenz;
        }*/
        knoten->adjazenzliste.clear();
        //delete knoten;
    }
    knoten.clear();

    for(int i=0; i<level->getROW(); i++)
    {
        for(int j=0; j<level->getCOL(); j++)
        {
            if(level->getTile(i,j)->onEnter(nullptr,nullptr))
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

std::vector<Graph::Knoten *> Graph::Knoten::getAdjazenzliste() const
{
    return adjazenzliste;
}

Graph::Knoten &Graph::Knoten::operator=(const Graph::Knoten &rhs)
{
    for(auto& adjazenz : adjazenzliste)
    {
        delete adjazenz;
    }

    getAdjazenzliste().resize(rhs.getAdjazenzliste().size());

    for(size_t i=0; i<rhs.adjazenzliste.size(); i++)
    {
        adjazenzliste.push_back(rhs.adjazenzliste.at(i));
    }

    bezeichnung.col = rhs.bezeichnung.col;
    bezeichnung.row = rhs.bezeichnung.row;

    return *this;
}
