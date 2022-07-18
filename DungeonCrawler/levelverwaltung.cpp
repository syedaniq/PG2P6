#include "levelverwaltung.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include "graph.h"
#include "level.h"

#include "controller.h"
#include "stationarycontroller.h"
#include "guardcontroller.h"
#include "attackcontroller.h"

Levelverwaltung::Levelverwaltung(string &dateiname) : dateiname(dateiname)
{
}

void Levelverwaltung::einlesen()
{
    ifstream quelle(dateiname.c_str(), ios::in);

     if (!quelle.good())
     {
       cerr << dateiname << " kann nicht geoeffnet werden!\n";
       exit(-1);
     }

         json jFile;
         quelle >> jFile;
         Level* l;

        for(const auto& item: jFile.items())
        {
           if(item.key()=="_level")
           {
               int row, col;
               for(const auto& valueItem: item.value().items())
               {
                   if(valueItem.key()=="cols")
                      col = valueItem.value();
                   if(valueItem.key()=="rows")
                       row = valueItem.value();
               }
               l = new Level(row,col);
           }

        }

        for(const auto& item: jFile["characters"])
        {
            int hp, row, col, stamina, strength;
            string controllerName;
            bool isHuman;
            Controller* controller;

            for(auto& values : item.items())
            {

                if(values.key() == "hp")
                    hp = values.value();
                if(values.key() == "row")
                    row = values.value();
                if(values.key() == "col")
                    col = values.value();
                if(values.key() == "stamina")
                    stamina = values.value();
                if(values.key() == "strength")
                    strength = values.value();
                if(values.key() == "texture")
                {
                    if(values.value() == "hero")
                        isHuman = true;
                    else
                        isHuman = false;
                }
                if(values.key() == "controller")
                {
                    cout << endl;
                    cout << "Hi" << endl;
                    cout << endl;
                    for(auto& iwas : values.value().items())
                    {
                        if(iwas.key() == "name")
                        {
                            if(iwas.value() == "stationarycontroller")
                                controller = new StationaryController;
                            if(iwas.value() == "uicontroller")
                                controller = l->getController();
                            if(iwas.value() == "attackcontroller")
                                controller = new AttackController(l);
                        }
                        if(iwas.key() == "movement")
                        {
                            string muster = iwas.value();
                            controller = new GuardController(muster);
                        }
                    }
                }

            }
            Character* c = new Character("x",1,controller,strength,stamina,isHuman);
            l->getCharacters().push_back(c);
            cout << "END OF FILE" << endl;
        }
         quelle.close();
}
