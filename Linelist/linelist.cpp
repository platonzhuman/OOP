#include "linelist.h"
#include <iostream>
using namespace std;

template <class T>
LineListElem<T>::LineListElem(const T& adata, LineListElem<T>* anext)
{
    data = adata;
    next = anext;
}

template <class T>
const T& LineListElem<T>::getData() const
{
    return data;
}

template <class T>
LineListElem<T>* LineListElem<T>::getNext()
{
    return next;
}

template <class T>
void LineList<T>::deleteFirst()
{
    if (start)
    {
        LineListElem<T>* temp = start->next;
        delete start;
        start = temp;
    }
    else throw LineListException();
}

template <class T>
LineList<T>::LineList()
{
    start = 0;
}

template <class T>
LineList<T>::~LineList()
{
    while (start)
        deleteFirst();
}

template <class T>
void LineList<T>::insertFirst(const T& data)
{
    LineListElem<T>* second = start;
    start = new LineListElem<T>(data, second);
}

template <class T>
void LineList<T>::deleteAfter(LineListElem<T>* ptr)
{
    if (ptr && ptr->next)
    {
        LineListElem<T>* temp = ptr->next;
        ptr->next = ptr->next->next;
        delete temp;
    }
    else throw LineListException();
}

template <class T>
void LineList<T>::insertAfter(LineListElem<T>* ptr, const T& data)
{
    if (ptr)
    {
        LineListElem<T>* temp = ptr->next;
        ptr->next = new LineListElem<T>(data, temp);
    }
}

template <class T>
LineListElem<T>* LineList<T>::getStart()
{
    return start;
}

template <class T>
ostream& operator<<(ostream& out, const LineList<T>& list)
{
    LineListElem<T>* ptr = list.start;
    if (!ptr)
        out << "EMPTY ";
    else
        while (ptr)
        {
            out << ptr->getData() << ' ';
            ptr = ptr->getNext();
        }
    return out;
}

// IOSEV

template <class T>
T LineList<T>::iosev(int k)
{
    //prov on pustot
    if (start == nullptr)
        throw LineListException();
    
    //poisk last el and podschet count
    LineListElem<T>* last = start;
    int count = 1;
    while (last->next != nullptr)
    {
        last = last->next;
        ++count;
    }
    last->next = start;

    // predudyshi
    LineListElem<T>* prew = last;
    //tekushi
    LineListElem<T>* curent = start;

    while(count > 1)
    {
        for (int i = 0; i < k; ++i)
        {
            prew = curent;
            curent = curent -> next;
        }
        //delete cur
        prew->next = curent->next;
        delete curent;

        curent = prew->next;
        --count;
    }
    T result = curent->data;

    curent->next = nullptr;
    start = curent;

    return result;
}


template class LineListElem<int>;
template class LineList<int>;
template ostream& operator<<(ostream& out, const LineList<int>& list);

