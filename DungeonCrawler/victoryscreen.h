#ifndef VICTORYSCREEN_H
#define VICTORYSCREEN_H

#include <QDialog>

class GraphicalUI;

namespace Ui {
class VictoryScreen;
}

class VictoryScreen : public QDialog
{
    Q_OBJECT

public:
    explicit VictoryScreen(GraphicalUI *g, QWidget *parent = nullptr);
    ~VictoryScreen();

private:
    Ui::VictoryScreen *ui;
};

#endif // VICTORYSCREEN_H
