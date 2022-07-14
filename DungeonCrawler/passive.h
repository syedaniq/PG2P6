#ifndef PASSIVE_H
#define PASSIVE_H
class Active;
class Passive
{
public:
    Passive();
    virtual void notify(Active *source) = 0;
};

#endif // PASSIVE_H
