#include "list.h"
#include <stdexcept>
using namespace std;
#include <iostream>

List::List()
{
}

void List::push_back(Level *l)
{
    Element *tmp = new Element{l, nullptr, nullptr};

    if (start == nullptr)
    {
        start = tmp;
    }
    else
    {
        Element *current = start;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = tmp;
        tmp->previous = current;
    }
    m_size++;
}

void List::push_front(Level *l)
{
    Element *oldStart = start;
    start = new Element{l, nullptr, nullptr};
    start->next = oldStart;
    oldStart->previous = start;

    m_size++;
}

void List::pop_back()
{
    if (start == nullptr)
        throw std::invalid_argument("Liste bereits leer!");

    if (start->next == nullptr)
    {
        delete start;
        start = nullptr;
        m_size--;
        return;
    }

    Element *current = start;
    while (current->next->next != nullptr)
        current = current->next;
    delete current->next;
    current->next = nullptr;
    m_size--;
}

void List::pop_front()
{
    if (start == nullptr)
        throw std::invalid_argument("Liste bereits leer!");

    Element *tmp = start->next;
    start->next->previous = nullptr;
    delete start;
    start = tmp;

    m_size--;
}

bool List::empty()
{
    return m_size == 0;
}

int List::size()
{
    return m_size;
}

void List::remove(Level *l)
{
    if (m_size == 0)
        return;

    if (m_size == 1)
    {
        if ((*start).data == l)
        {
            delete start;
            start = nullptr;
            m_size--;
        }
        return;
    }

    Element *current = start;
    while (current != nullptr)
    {
        if (current->data == l)
        {
            Element *tmp = current->next;
            if (current == start)
            {
                if (current->next != nullptr)
                    current->next->previous = nullptr;
                start = current->next;
            }
            else if (current->next == nullptr)
            {
                current->previous->next = nullptr;
            }
            else
            {
                current->previous->next = current->next;
                current->next->previous = current->previous;
            }
            delete current;
            current = tmp;
            m_size--;
        }
        else
            current = current->next;
    }
}

List::iterator List::begin()
{
    return start;
}

List::iterator List::end()
{
    Element *current = start;
    while (current->next)
    {
        current = current->next;
    }
    return current;
}

List::iterator::iterator(List::Element *element) : element(element)
{
}

List::iterator &List::iterator::operator++()
{
    if (element->next != nullptr)
        element = element->next;
    else
        throw invalid_argument("Keine weiteren Elemente vorhanden!");

    return *this;
}

List::iterator &List::iterator::operator--()
{
    if (element->previous == nullptr)
        throw invalid_argument("Cannot call -- Operation on first Element!");
    element = element->previous;
    return *this;
}

Level *&List::iterator::operator*()
{
    return element->data;
}

bool List::iterator::operator==(const iterator &it)
{
    return it.element == element;
}

bool List::iterator::operator!=(const List::iterator &it)
{
    return !(it.element == element);
}
