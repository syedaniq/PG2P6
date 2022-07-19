#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "door.h"
#include "graphicalui.h"
#include "pit.h"
#include "portal.h"
#include <QPushButton>
#include <iostream>

#include "levelchanger.h"
#include "wall.h"
#include "floor.h"
#include "ramp.h"
#include "switch.h"
#include "lootchest.h"

void MainWindow::Knoepfe()
{
    buttons = new QGroupBox(this);
    buttons->setGeometry(800, 200, 250, 250);
    buttons->setStyleSheet("border:0;");

    gridlayout2 = new QGridLayout(this);
    gridlayout2->setSpacing(0);
    buttons->setLayout(gridlayout2);

    QPushButton *btn7 = new QPushButton(this);
    btn7->setIcon(g->arrows.at(6));
    gridlayout2->addWidget(btn7, 0, 0);
    btn7->setIconSize(QSize(50, 50));
    connect(btn7, &QPushButton::clicked, this,
            [this]()
            { g->lastInput = 7; });

    QPushButton *btn8 = new QPushButton(this);
    btn8->setIcon(g->arrows.at(7));
    gridlayout2->addWidget(btn8, 0, 1);
    btn8->setIconSize(QSize(50, 50));
    connect(btn8, &QPushButton::clicked, this,
            [this]()
            { g->lastInput = 8; });

    QPushButton *btn9 = new QPushButton(this);
    btn9->setIcon(g->arrows.at(8));
    gridlayout2->addWidget(btn9, 0, 2);
    btn9->setIconSize(QSize(50, 50));
    connect(btn9, &QPushButton::clicked, this,
            [this]()
            { g->lastInput = 9; });

    QPushButton *btn4 = new QPushButton(this);
    btn4->setIcon(g->arrows.at(3));
    gridlayout2->addWidget(btn4, 1, 0);
    btn4->setIconSize(QSize(50, 50));
    connect(btn4, &QPushButton::clicked, this,
            [this]()
            { g->lastInput = 4; });

    QPushButton *btn5 = new QPushButton(this);
    btn5->setIcon(g->arrows.at(4));
    gridlayout2->addWidget(btn5, 1, 1);
    btn5->setIconSize(QSize(50, 50));
    connect(btn5, &QPushButton::clicked, this,
            [this]()
            { g->lastInput = 5; });

    QPushButton *btn6 = new QPushButton(this);
    btn6->setIcon(g->arrows.at(5));
    gridlayout2->addWidget(btn6, 1, 2);
    btn6->setIconSize(QSize(50, 50));
    connect(btn6, &QPushButton::clicked, this,
            [this]()
            { g->lastInput = 6; });

    QPushButton *btn1 = new QPushButton(this);
    btn1->setIcon(g->arrows.at(0));
    gridlayout2->addWidget(btn1, 2, 0);
    btn1->setIconSize(QSize(50, 50));
    connect(btn1, &QPushButton::clicked, this,
            [this]()
            { g->lastInput = 1; });

    QPushButton *btn2 = new QPushButton(this);
    btn2->setIcon(g->arrows.at(1));
    gridlayout2->addWidget(btn2, 2, 1);
    btn2->setIconSize(QSize(50, 50));
    connect(btn2, &QPushButton::clicked, this,
            [this]()
            { g->lastInput = 2; });

    QPushButton *btn3 = new QPushButton(this);
    btn3->setIcon(g->arrows.at(2));
    gridlayout2->addWidget(btn3, 2, 2);
    btn3->setIconSize(QSize(50, 50));
    connect(btn3, &QPushButton::clicked, this,
            [this]()
            { g->lastInput = 3; });


    saveBox = new QGroupBox(this);
    saveBox->setGeometry(875, 475, 100, 50);
    saveBox->setStyleSheet("border:0;");

    saveLayout = new QGridLayout(this);
    saveLayout->setSpacing(0);
    saveBox->setLayout(saveLayout);

    QPushButton *saveBtn = new QPushButton(this);
    saveBtn->setIcon(g->save);
    saveLayout->addWidget(saveBtn, 0, 0);
    saveBtn->setIconSize(QSize(150, 300));
    connect(saveBtn, &QPushButton::clicked, this,
            [this]()
            { g->lastInput = 7; });
}

void MainWindow::spielfeldSetzen(Level *level)
{
    for (auto tile : field)
    {
        delete tile;
    }
    field.clear();
    if (gridlayout != nullptr)
    {
        for (int i = 0; i < gridlayout->count(); i++)
        {
            delete gridlayout->itemAt(i)->widget();
        }
        delete gridlayout;
    }

    spielfeld->setGeometry(100, 200, 600, 350);
    spielfeld->setStyleSheet("border:0;");

    gridlayout = new QGridLayout();
    gridlayout->setSpacing(0);
    spielfeld->setLayout(gridlayout);

    for (size_t i = 0; i < level->getField().size(); i++)
    {
        for (size_t j = 0; j < level->getField().at(i).size(); j++)
        {
            QLabel *label = new QLabel(this);
            label->setScaledContents(true);

            setJeweiligePixmap(level->getTile(i, j), label);

            field.push_back(label);
            gridlayout->addWidget(label, i, j);
            label->show();
            label->raise();

            if (level->getTile(i, j)->hasCharacter() and level->getTile(i, j)->getCharacter()->getIsHuman())
            {
                if (level->getTile(i, j)->getCharacter()->getHitpoints() > 0)
                {
                    character = new QLabel(this);
                    character->setScaledContents(true);
                    character->setPixmap(g->front.at(1));

                    field.push_back(character);
                    gridlayout->addWidget(character, i, j);

                    character->raise();
                }
                continue;
            }
            else if (level->getTile(i, j)->hasCharacter() && !level->getTile(i, j)->getCharacter()->getIsHuman())
            {
                if (level->getTile(i, j)->getCharacter()->getHitpoints() > 0)
                {
                    zombie = new QLabel(ui->centralwidget);
                    zombie->setScaledContents(true);

                    zombie->setPixmap(g->zombie[rand() % 2]);

                    field.push_back(zombie);
                    gridlayout->addWidget(zombie, i, j);

                    zombie->raise();
                }
                continue;
            }
        }
    }

    if (!drawButtons)
    {
        Knoepfe();
        drawButtons = true;
    }
}

void MainWindow::spielfeldUpdaten(Level *level)
{

    for (size_t i = 0; i < level->getField().size(); i++)
    {
        for (size_t j = 0; j < level->getField().at(i).size(); j++)
        {
            if (level->getTile(i, j)->getCharacterDied())
            {
                QLabel *label = new QLabel(this);
                label->setScaledContents(true);

                setJeweiligePixmap(level->getTile(i, j), label);

                field.at(i) = label;
                gridlayout->removeWidget(field.at(i));
                gridlayout->addWidget(label, i, j);
                label->show();
                label->raise();
                level->getTile(i, j)->setCharacterDied(false);
            }
        }
    }
}

void MainWindow::updateField(Level *level)
{
    if (level->getCharacters().at(0)->getHitpoints() <= 0)
    {
        g->hasLost();
    }

    ui->statusbar->setFont(QFont("Arial", 12, QFont::Bold));
    ui->statusbar->showMessage("HP: " + QString::number(level->getCharacters().at(0)->getHitpoints()) + "/" + QString::number(level->getCharacters().at(0)->getMaxHP()) + " | Strength: " + QString::number(level->getCharacters().at(0)->getStrength()) + " | Stamina: " + QString::number(level->getCharacters().at(0)->getStamina()));
    ui->statusbar->raise();

    if (level->removeDeadPlayers() == true)
        spielfeldUpdaten(level);

    for (size_t i = 0; i < level->getField().size(); i++)
    {
        for (size_t j = 0; j < level->getField().at(i).size(); j++)
        {

            if (level->getTile(i, j)->hasCharacter() and level->getTile(i, j)->getCharacter()->getHitpoints() > 0)
            {
                if (level->getTile(i, j)->getCharacter()->getIsHuman())
                {
                    gridlayout->removeWidget(character);
                    gridlayout->addWidget(character, i, j);
                    character->raise();
                }
                else
                {
                    gridlayout->removeWidget(zombie);
                    gridlayout->addWidget(zombie, i, j);
                    zombie->raise();
                }

                if (typeid(*level->getTile(i, j)) == typeid(Pit))
                {
                    auto pit = gridlayout->itemAtPosition(i, j);
                    QLabel *label = dynamic_cast<QLabel *>(pit->widget());
                    label->raise();
                    if (level->getTile(i, j)->getCharacter()->getIsHuman())
                        character->lower();
                    continue;
                }

                character->show();
            }

            if (level->getTile(i, j)->getTexture() == "/" or
                level->getTile(i, j)->getTexture() == "X")
            {
                auto item = gridlayout->itemAtPosition(i, j);
                QLabel *label = dynamic_cast<QLabel *>(item->widget());
                int open;
                if (level->getTile(i, j)->getTexture() == "/")
                    open = 1;
                else
                    open = 0;
                label->setPixmap(g->doors.at(open));
            }
        }
    }
}

void MainWindow::setJeweiligePixmap(Tile *tile, QLabel *label)
{
    if (typeid(*tile) == typeid(Wall))
        label->setPixmap(g->wall[0]);
    else if (typeid(*tile) == typeid(Door))
    {
        Door *p = dynamic_cast<Door *>(tile);
        label->setPixmap(g->doors.at(p->getOpen()));
    }
    else if (typeid(*tile) == typeid(Floor))
        label->setPixmap(g->floor[rand() % 5]);
    else if (typeid(*tile) == typeid(Pit))
        label->setPixmap(g->pit);
    else if (typeid(*tile) == typeid(Portal))
    {
        Portal *p = dynamic_cast<Portal *>(tile);
        label->setPixmap(g->portal[p->getPortalType()]);
    }
    else if (typeid(*tile) == typeid(Ramp))
        label->setPixmap(g->ramp);
    else if (typeid(*tile) == typeid(Switch))
        label->setPixmap(g->switchTile);
    else if (typeid(*tile) == typeid(LevelChanger))
        label->setPixmap(g->levelchanger);
    else if (typeid(*tile) == typeid(Lootchest))
        label->setPixmap(g->chest);
}

MainWindow::MainWindow(GraphicalUI *g, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), g(g)
{
    QWidget::setStyleSheet("background-color: rgba(0,0,0,0%)");
    ui->setupUi(this);

    this->setGeometry(0, 0, 1200, 700);

    QLabel *hintergrund = new QLabel(this);
    hintergrund->setGeometry(0, 0, 1200, 700);
    hintergrund->setPixmap(g->bloodyFrame);
    hintergrund->setScaledContents(true);
    spielfeld = new QGroupBox(this);

    // spielfeldSetzen(g);
}

MainWindow::~MainWindow()
{
    delete ui;
}
