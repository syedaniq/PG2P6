#ifndef LEVEL_H
#define LEVEL_H
#include <QVector>
#include <array>
#include <vector>
using namespace std;
#include "character.h"
#include "tile.h"
#include "graph.h"
class Level
{
public:
    Level(const Level &level);
    Level(Controller *controller, int x);
    ~Level();
    Level &operator=(const Level &rhs);

    Tile *getTile(int row, int col);
    const Tile *getTile(int row, int col) const;
    void placeCharacter(Character *c, int row, int col);

    vector<vector<Tile *>> &getField();
    QVector<Character *> &getCharacters();

    int getROW() const;
    int getCOL() const;
    vector<vector<Tile *>> field;
    void removePlayer();
    bool removeDeadPlayers();
    void addPlayer(Character *c);

    QVector<Character *> characters;

    Controller *getController() const;

    Graph *getGraph() const;
    void setGraph(Graph *value);

    vector<int> getPath();

protected:
    const int ROW;
    const int COL;

private:
    Controller *controller;
    Graph *graph;
};

#endif // LEVEL_H
