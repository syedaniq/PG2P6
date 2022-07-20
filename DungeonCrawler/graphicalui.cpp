#include "graphicalui.h"
#include <QTest>
#include <iostream>
#include <string>
// #include "startscreen.ui"

GraphicalUI::GraphicalUI()
{
    setPixmaps();
    start = new StartScreen(this);
    main = new MainWindow(this);
    win = new VictoryScreen(this);
    lose = new LoseScreen(this);
    start->show();
}

void GraphicalUI::fillVec(QVector<QPixmap> &v, int size, string path)
{
    for (int i = 0; i < size; i++)
    {
        string pfad = ":/textures/";
        pfad.append(path);
        pfad.append("/");
        pfad.append(to_string(i + 1));
        pfad.append(".png");
        v.push_back(QPixmap(pfad.c_str()));
    }
}

void GraphicalUI::fillAllVecs()
{
    fillVec(arrows, 9, "arrows");
    fillVec(front, 3, "front");
    fillVec(back, 3, "back");
    fillVec(right, 3, "right");
    fillVec(left, 3, "left");
    fillVec(doors, 2, "doors");
    fillVec(floor, 5, "floor");
    fillVec(portal, 3, "portal");
    fillVec(wall, 1, "wall");
    fillVec(zombie, 2, "zombie");
}

void GraphicalUI::setPixmaps()
{
    fillAllVecs();
    startScreen = QPixmap(":/textures/startscreen.png");
    newGame = QPixmap(":/textures/new_game_button.png");
    bloodyFrame = QPixmap(":/textures/bloody_frame.png");
    pit = QPixmap(":/textures/pit.png");
    ramp = QPixmap(":/textures/ramp.png");
    switchTile = QPixmap(":/textures/switch.png");
    charComplete = QPixmap(":/textures/char_complete.png");
    chest = QPixmap(":/textures/chest.png");
    levelchanger = QPixmap(":/textures/levelchanger.png");
    winScreen = QPixmap(":/textures/victory.png");
    defeatScreen = QPixmap(":/textures/wasted.png");
    save = QPixmap(":/textures/save.png");
    goblin = QPixmap(":/textures/goblin_down.png");
}

void GraphicalUI::switchWindow()
{
    start->hide();
    main->show();
}

void GraphicalUI::levelSwitchInit()
{
    drawn = false;
}

void GraphicalUI::hasWon()
{
    win->show();
    main->close();
    QTest::qWait(2000);
    exit(0);
}

void GraphicalUI::hasLost()
{
    lose->show();
    main->close();
    QTest::qWait(2000);
    exit(0);
}

int GraphicalUI::move()
{
    QTest::qWait(50);
    QCoreApplication::processEvents();
    if (lastInput != 10)
    {
        if (lastInput == 1)
        {
            main->character->setPixmap(front.at(0));
            QTest::qWait(50);
            main->character->setPixmap(left.at(0));
        }
        else if (lastInput == 2)
        {
            main->character->setPixmap(front.at(2));
            QTest::qWait(50);
            main->character->setPixmap(front.at(1));
        }
        else if (lastInput == 3)
        {
            main->character->setPixmap(front.at(2));
            QTest::qWait(50);
            main->character->setPixmap(right.at(0));
        }
        else if (lastInput == 4)
        {
            main->character->setPixmap(left.at(0));
            QTest::qWait(50);
            main->character->setPixmap(left.at(1));
        }
        else if (lastInput == 5)
        {
            main->character->setPixmap(front.at(1));
        }
        else if (lastInput == 6)
        {
            main->character->setPixmap(right.at(0));
            QTest::qWait(50);
            main->character->setPixmap(right.at(1));
        }
        else if (lastInput == 7)
        {
            main->character->setPixmap(back.at(0));
            QTest::qWait(50);
            main->character->setPixmap(left.at(1));
        }
        else if (lastInput == 8)
        {
            main->character->setPixmap(back.at(0));
            QTest::qWait(50);
            main->character->setPixmap(back.at(2));
        }
        else if (lastInput == 9)
        {
            main->character->setPixmap(back.at(2));
            QTest::qWait(50);
            main->character->setPixmap(right.at(2));
        }
        else
            cout << "Keine Eingabe erkannt!" << endl;

        int temp = lastInput;
        lastInput = 10;
        return temp;
    }
    return lastInput;
}

void GraphicalUI::draw(Level *level)
{
    if (!drawn)
    {
        main->spielfeldSetzen(level);
        drawn = true;
        main->repaint();
    }
    else
    {
        main->updateField(level);
    }
}
