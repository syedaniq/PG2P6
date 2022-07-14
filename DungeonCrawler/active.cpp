#include "active.h"
#include <iostream>
using namespace std;
Active::Active()
{
}

const std::vector<Passive *> &Active::getPassiveList() const
{
    return passiveList;
}

void Active::attach(Passive *p)
{
}

void Active::detach(Passive *p)
{
}

void Active::activate()
{
}
