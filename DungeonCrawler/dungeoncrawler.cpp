#include "dungeoncrawler.h"
#include "levelchanger.h"
#include <iostream>
using std::cout;
using std::endl;

#include "switch.h"
#include "lootchest.h"

DungeonCrawler::DungeonCrawler(AbstractUI *abstractUI, Level *currentLevel)
    : abstractUI(abstractUI), currentLevel(currentLevel)
{
}

DungeonCrawler::DungeonCrawler(AbstractUI *abstractUI)
 : abstractUI(abstractUI)
{

}
#include "attackcontroller.h"
void DungeonCrawler::play()
{
    for(int i=0; i<levels.size();i++){
        if(!levels.at(i)->characters.empty())
            if(levels.at(i)->characters.at(0)->getIsHuman()){
                currentLevel=levels.at(i);
                currentLevel->getCharacters().at(0)->setController(levels.at(0)->getController());
            }
    }

    for(int c=0; c<levels.size(); c++)
    {
        for(int i=0; i<levels.at(c)->getROW(); i++)
        {
            for(int j=0; j<levels.at(c)->getCOL(); j++)
            {
                if(typeid (*levels.at(c)->getTile(i,j)) == typeid(LevelChanger))
                {
                    LevelChanger *lc = dynamic_cast<LevelChanger*>(levels.at(c)->getTile(i,j));
                    lc->setToLevel(levels.at(lc->getDestLevelIndex()));
                }
            }
        }
    }

    // 1. moveAufruf für jede Figur
    while (1)
    {
        currentLevel->getGraph()->update();
        abstractUI->draw(currentLevel);
        GraphicalUI* graphicalUI = dynamic_cast<GraphicalUI*>(abstractUI);
        graphicalUI->updateList(&levels);

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

                            if(typeid(*currentLevel->getTile((currentRow+newRow), (currentCol+newCol)))==typeid(Lootchest))
                            {
                                Lootchest* lc = dynamic_cast<Lootchest*>(currentLevel->getTile((currentRow+newRow), (currentCol+newCol)));
                                lc->setG(dynamic_cast<GraphicalUI*>(abstractUI));
                            }

                            if(typeid(*currentLevel->getTile((currentRow+newRow), (currentCol+newCol)))==typeid(Switch))
                            {
                                currentLevel->getGraph()->update();
                            }

                            if(typeid (*currentLevel->getTile(currentRow + newRow, currentCol + newCol)) == typeid(LevelChanger))
                            {
                                LevelChanger *lc = dynamic_cast<LevelChanger*>(currentLevel->getTile(currentRow + newRow, currentCol + newCol));
                                lc->setToLevel(levels.at(lc->getDestLevelIndex()));
                            }
                            who->getTile()->moveTo(currentLevel->getTile(currentRow + newRow, currentCol + newCol), who);
                            mainHasMoved = true;
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
