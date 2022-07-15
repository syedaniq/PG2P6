#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include "abstractui.h"
#include "controller.h"
#include "mainwindow.h"
#include "startscreen.h"
#include "victoryscreen.h"
#include "losescreen.h"
#include <QPixmap>

class GraphicalUI : public AbstractUI, public Controller
{
public:
    GraphicalUI();
    void fillVec(QVector<QPixmap> &v, int size, string path);
    void fillAllVecs();
    void setPixmaps();
    void switchWindow();

public:
    QPixmap startScreen, newGame, bloodyFrame, pit, ramp, switchTile, charComplete, chest, levelchanger, winScreen, defeatScreen;
    QVector<QPixmap> arrows, back, front, left, right, doors, floor, portal, wall, zombie;
    int lastInput = 10;
    void levelSwitchInit();

    void hasWon();
    void hasLost();

    // Controller interface
public:
    int move();

    // AbstractUI interface
public:
    void draw(Level *level);

private:
    StartScreen *start;
    MainWindow *main;
    VictoryScreen *win;
    LoseScreen *lose;
    bool drawn = false;
};

#endif // GRAPHICALUI_H
