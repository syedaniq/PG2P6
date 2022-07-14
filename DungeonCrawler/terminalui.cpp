#include "terminalui.h"
#include <iostream>
using namespace std;

TerminalUI::TerminalUI()
{
}

void TerminalUI::draw(Level *level)
{
    for (size_t i = 0; i < level->getField().size(); i++)
    {
        for (size_t j = 0; j < level->getField().at(i).size(); j++)
        {
            if (level->getTile(i, j)->hasCharacter())
                cout << level->getField().at(i).at(j)->getCharacter()->getTexture() << " ";

            else
                cout << level->getField().at(i).at(j)->getTexture() << " ";
        }
        cout << endl;
    }
}

int TerminalUI::move()
{
    int eingabe;
    do
    {
        cout << "Geben Sie eine Bewegungsrichtung an: ";
        cin >> eingabe;

    } while ((eingabe > 9) or (eingabe < 0));

    return eingabe;
}
