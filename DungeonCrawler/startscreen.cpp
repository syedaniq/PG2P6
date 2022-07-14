#include "startscreen.h"
#include "ui_startscreen.h"

#include <QLabel>
#include "graphicalui.h"
#include <QBitmap>
#include <QPushButton>

StartScreen::StartScreen(GraphicalUI *g, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    QWidget::setStyleSheet("background-color: black;");
    ui->setupUi(this);
    this->setGeometry(0,0,1200,700);
    QLabel* label =  new QLabel(this);
    label->setGeometry(0,0,1200,700);

    label->setPixmap(g->startScreen);
    label->setScaledContents(true);

    QPushButton* btn = new QPushButton(this);
    btn->setIcon(QIcon(":/textures/new_game_button.png"));
    btn->setIconSize(QSize(270,200));
    btn->setGeometry((1200/2)-(270/2),500,270,200);

    connect(btn, &QPushButton::clicked, this, [g](){g->switchWindow();});
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::hideStartMenu()
{
    //nicht noetig
}
