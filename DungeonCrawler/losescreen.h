#ifndef LOSESCREEN_H
#define LOSESCREEN_H

#include <QDialog>

class GraphicalUI;

namespace Ui
{
    class LoseScreen;
}

class LoseScreen : public QDialog
{
    Q_OBJECT

public:
    explicit LoseScreen(GraphicalUI *g, QWidget *parent = nullptr);
    ~LoseScreen();

private:
    Ui::LoseScreen *ui;
};

#endif // LOSESCREEN_H
