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
    Levelverwaltung();
    void einlesen(std::string& dateiname);
    void einspeichern(Level* level);
};

#endif // LEVELVERWALTUNG_H
