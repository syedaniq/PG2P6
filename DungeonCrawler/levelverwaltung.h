#ifndef LEVELVERWALTUNG_H
#define LEVELVERWALTUNG_H

#include "json.hpp"
#include <string>
#include "level.h"
using namespace std;
using namespace nlohmann;

class Levelverwaltung
{
public:
    Levelverwaltung(std::string& dateiname);
    void einlesen();
    void einspeichern(Level* level);
private:
    string& dateiname;
};

#endif // LEVELVERWALTUNG_H
