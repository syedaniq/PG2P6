#ifndef LEVELVERWALTUNG_H
#define LEVELVERWALTUNG_H

#include "json.hpp"
#include <string>

using namespace std;
using namespace nlohmann;

class Levelverwaltung
{
public:
    Levelverwaltung(std::string& dateiname);
    void einlesen();
private:
    string& dateiname;
};

#endif // LEVELVERWALTUNG_H
