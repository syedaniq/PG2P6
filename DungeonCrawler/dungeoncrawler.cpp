#include "dungeoncrawler.h"
#include "levelchanger.h"
#include <iostream>
using std::cout;
using std::endl;

#include "switch.h"

DungeonCrawler::DungeonCrawler(AbstractUI *abstractUI, Level *currentLevel)
    : abstractUI(abstractUI), currentLevel(currentLevel)
{
}

void DungeonCrawler::play()
{
    // 1. moveAufruf für jede Figur
    while (1)
    {

        abstractUI->draw(currentLevel);

        int richtung;
        int currentRow = -1;
        int currentCol = -1;
        bool mainHasMoved = false;

        for (int i = 0; i < currentLevel->getCharacters().size(); i++)
        {
            if (currentLevel->getCharacters().at(i)->getIsHuman() or mainHasMoved)
            {
                richtung = currentLevel->getCharacters().at(i)->move();
                if (richtung == 10)
                    continue;

                cout << richtung << endl;

                Tile *currentTile = currentLevel->getCharacters().at(i)->getTile();
                currentRow = currentTile->getRow();
                currentCol = currentTile->getCol();

                if (richtung != 0)
                {
                    int newRow = 0;
                    int newCol = 0;
                    Character *who = currentLevel->getField().at(currentRow).at(currentCol)->getCharacter();
                    if (richtung == 1)
                    {
                        newRow++;
                        newCol--;
                    }
                    else if (richtung == 2)
                    {
                        newRow++;
                    }
                    else if (richtung == 3)
                    {
                        newRow++;
                        newCol++;
                    }
                    else if (richtung == 4)
                    {
                        newCol--;
                    }
                    else if (richtung == 5)
                    {
                        newCol = 0;
                        newRow = 0;
                    }
                    else if (richtung == 6)
                    {
                        newCol++;
                    }
                    else if (richtung == 7)
                    {
                        newRow--;
                        newCol--;
                    }
                    else if (richtung == 8)
                    {
                        newRow--;
                    }
                    else if (richtung == 9)
                    {
                        newRow--;
                        newCol++;
                    }
                    if ((currentRow + newRow >= 0 and currentRow + newRow < currentLevel->getROW()) && (currentCol + newCol >= 0 and currentCol + newCol < currentLevel->getCOL()))
                    {
                        if (who)
                        {
                            who->getTile()->moveTo(currentLevel->getTile(currentRow + newRow, currentCol + newCol), who);
                            mainHasMoved = true;

                            if(typeid(*currentLevel->getTile((currentRow+newRow), (currentCol+newCol)))==typeid(Switch))
                            {
                                currentLevel->getGraph()->update();
                            }
                        }
                    }
                    else
                    {
                        cout << "Ungueltige Eingabe!" << endl;
                        continue;
                    }
                }
                else
                    return;
            }
        }
    }
}

void DungeonCrawler::addLevel(Level *l)
{
    levels.push_back(l);
}

void DungeonCrawler::setLevel(Level *l)
{
    currentLevel = l;
}

void DungeonCrawler::notify(Active *source)
{
    Level *oldLevel = currentLevel;
    LevelChanger *lc = dynamic_cast<LevelChanger *>(source);
    currentLevel = lc->getToLevel();
    currentLevel->addPlayer(oldLevel->getCharacters().at(0));
    oldLevel->removePlayer();
    currentLevel->getCharacters().at(0)->setTile(lc->getDestTile());
    dynamic_cast<GraphicalUI *>(abstractUI)->levelSwitchInit();
}
