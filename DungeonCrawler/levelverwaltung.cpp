#include "levelverwaltung.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
Levelverwaltung::Levelverwaltung(string &dateiname) : dateiname(dateiname)
{
}

void Levelverwaltung::einlesen()
{
    ifstream quelle(dateiname);
         if (!quelle.good())
         {
           cerr << dateiname << " kann nicht geoeffnet werden!\n";
           exit(-1);
         }
         quelle.close();
}
