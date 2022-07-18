#include "levelverwaltung.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include "graph.h"
#include "level.h"
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

        for(const auto& item: jFile.items())
        {
           if(item.key()=="_level")
           {
               int col=0; int row=0;
                for(const auto& valueItem: item.value().items())
                {
                    if(valueItem.key()=="cols")
                       cout<< valueItem.value();
                    if(valueItem.key()=="rows")
                        cout << valueItem.value();
                }
           }

        }


         quelle.close();
}
