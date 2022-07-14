#include "victoryscreen.h"
#include "ui_victoryscreen.h"

#include <QLabel>
#include "graphicalui.h"

VictoryScreen::VictoryScreen(GraphicalUI *g, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VictoryScreen)
{
    ui->setupUi(this);
    QLabel* label =  new QLabel(this);
    label->setGeometry(0,0,634,496);
    resize(634, 496);
    label->setPixmap(g->winScreen);
    label->setScaledContents(true);

}

VictoryScreen::~VictoryScreen()
{
    delete ui;
}
