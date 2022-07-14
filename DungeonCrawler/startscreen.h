#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>

namespace Ui {
class StartScreen;
}

class GraphicalUI;

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(GraphicalUI* g, QWidget *parent = nullptr);
    ~StartScreen();

private:
    Ui::StartScreen *ui;

private slots:
    void hideStartMenu();

signals:
    void clickedStartGame();
};

#endif // STARTSCREEN_H
