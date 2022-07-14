#include "guardcontroller.h"

GuardController::GuardController(std::string &muster) : muster(muster)
{
}

int GuardController::move()
{
    if ((size_t)index == muster.size())
        index = 0;
    char number = muster.at(index);
    index++;
    return number - '0';
}

std::string GuardController::getMuster() const
{
    return muster;
}

void GuardController::setMuster(const std::string &value)
{
    muster = value;
}
