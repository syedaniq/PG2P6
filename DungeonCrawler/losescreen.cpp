#include "losescreen.h"
#include "ui_losescreen.h"

#include <QLabel>
#include "graphicalui.h"

LoseScreen::LoseScreen(GraphicalUI *g, QWidget *parent) : QDialog(parent),
                                                          ui(new Ui::LoseScreen)
{
    ui->setupUi(this);
    QLabel *label = new QLabel(this);
    label->setGeometry(0, 0, 1280, 720);
    resize(1280, 720);
    label->setPixmap(g->defeatScreen);
    label->setScaledContents(true);
}

LoseScreen::~LoseScreen()
{
    delete ui;
}
