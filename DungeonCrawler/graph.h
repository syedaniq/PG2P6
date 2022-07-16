#ifndef GRAPH_H
#define GRAPH_H

class Level;
class Tile;
#include <list>
#include <vector>

class Graph
{
public:
    struct Knoten
    {
        struct Name
        {
            int row;
            int col;
        };

        Name bezeichnung;
        std::vector<Knoten*>adjazenzliste;

        bool operator==(const Knoten& rhs)
        {
            return (this->bezeichnung.col == rhs.bezeichnung.col)
                    and (this->bezeichnung.row == rhs.bezeichnung.row);
        }
    public:
        std::vector<Knoten *> getAdjazenzliste() const;
        Knoten& operator=(const Knoten& rhs);
        bool besucht = false;
        Knoten* parent = nullptr;
    };

    Graph(Level* level);
    void addKnoten(Tile* t);
    Knoten* findKnoten(int row, int col);
    void addNachbarKanten(Tile* from);
    void addKante(Tile* from, Tile* to);
    void update();
    void print();
    std::vector<Knoten *> getKnoten() const;

private:
    Level* level;
    std::vector<Knoten*>knoten;
};

#endif // GRAPH_H
