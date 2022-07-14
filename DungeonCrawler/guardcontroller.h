#ifndef GUARDCONTROLLER_H
#define GUARDCONTROLLER_H

#include "controller.h"
#include <string>

class GuardController : public Controller
{
public:
    GuardController(std::string &muster);

    // Controller interface
public:
    int move() override;
    std::string getMuster() const;
    void setMuster(const std::string &value);

private:
    std::string muster;
    int index = 0;
};

#endif // GUARDCONTROLLER_H
