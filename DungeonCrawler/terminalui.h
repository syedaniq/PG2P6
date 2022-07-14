#ifndef TERMINALUI_H
#define TERMINALUI_H
#include "abstractui.h"
#include "controller.h"
class TerminalUI : public AbstractUI, public Controller
{
public:
    TerminalUI();

    // AbstractUI interface
public:
    void draw(Level *level) override;

    // Controller interface
public:
    int move() override;
};

#endif // TERMINALUI_H
