#ifndef ACTIVE_H
#define ACTIVE_H
#include "passive.h"
#include <vector>
class Tile;

class Active
{
public:
    Active();
    virtual void attach(Passive *p) = 0;
    virtual void detach(Passive *p) = 0;
    virtual void activate() = 0;
    virtual const std::vector<Passive *> &getPassiveList() const;

private:
protected:
    std::vector<Passive *> passiveList;
};

#endif // ACTIVE_H
