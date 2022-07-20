#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class GraphicalUI;

#include <QGridLayout>
#include <QGroupBox>

namespace Ui
{
    class MainWindow;
}

#include "level.h"
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(GraphicalUI *g, QWidget *parent = nullptr);
    ~MainWindow();
    GraphicalUI *g;
    void spielfeldSetzen(Level *level);
    void spielfeldUpdaten(Level *level);
    void updateField(Level *level);
    void setJeweiligePixmap(Tile *tile, QLabel *label);
    QLabel *character;
    QLabel *zombie;
    QLabel *goblin;
    void Speichern();
    void Knoepfe(Level* level);

private:
    Ui::MainWindow *ui;
    std::vector<QLabel *> field;
    QGroupBox *spielfeld = nullptr;
    QGridLayout *gridlayout = nullptr;
    QGroupBox *buttons = nullptr;
    QGridLayout *gridlayout2 = nullptr;
    QGroupBox *saveBox = nullptr;
    QGridLayout *saveLayout = nullptr;
    bool drawButtons = false;
};

#endif // MAINWINDOW_H
