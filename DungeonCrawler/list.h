#ifndef LIST_H
#define LIST_H

#include "level.h"

using sizee_t = int; // connected noch nicht für size_t

class List
{
public:
    struct Element
    {
        Level *data;
        Element *next;
        Element *previous;
    };

    class iterator
    {
    public:
        iterator(Element *element);
        iterator &operator++();
        iterator &operator--();
        Level *&operator*();
        bool operator==(const iterator &);
        bool operator!=(const iterator &);

    private:
        Element *element;
    };

    List();
    void push_back(Level *l);
    void push_front(Level *l);
    void pop_back();
    void pop_front();
    bool empty();
    int size();
    void remove(Level *l);
    iterator begin();
    iterator end();

private:
    Element *start = nullptr;
    int m_size = 0;
};

#endif // LIST_H
