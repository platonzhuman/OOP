#include "linelist_plus.h"
#include <iostream>
using namespace std;

template <class T>
LineListElem<T>::LineListElem(const T &adata, LineListElem<T> *anext)
{
    data = adata;
    next = anext;
}

template <class T>
const T &LineListElem<T>::getData() const
{
    return data;
}

template <class T>
LineListElem<T> *LineListElem<T>::getNext()
{
    return next;
}

template <class T>
void LineList<T>::deleteFirst()
{
    if (start)
    {
        LineListElem<T> *temp = start->next;
        delete start;
        start = temp;
        if (!start)
            last = nullptr;
    }
    else
        throw LineListException();
}

template <class T>
LineList<T>::LineList() : start(nullptr), last(nullptr) {}

template <class T>
LineList<T>::~LineList()
{
    while (start)
        deleteFirst();
}

template <class T>
void LineList<T>::insertFirst(const T &data)
{
    LineListElem<T> *second = start;
    start = new LineListElem<T>(data, second);
    if (!last)
        last = start;
}

template <class T>
void LineList<T>::deleteAfter(LineListElem<T> *ptr)
{
    if (ptr && ptr->next)
    {
        LineListElem<T> *temp = ptr->next;
        ptr->next = ptr->next->next;
        if (temp == last)
            last = ptr;
        if (temp == start)
            start = ptr->next;
        delete temp;
    }
    else
        throw LineListException();
}

template <class T>
void LineList<T>::insertAfter(LineListElem<T> *ptr, const T &data)
{
    if (ptr)
    {
        LineListElem<T> *temp = ptr->next;
        ptr->next = new LineListElem<T>(data, temp);
        if (ptr == last)
            last = ptr->next;
    }
}

template <class T>
LineListElem<T> *LineList<T>::getStart()
{
    return start;
}

template <class T>
ostream &operator<<(ostream &out, const LineList<T> &list)
{
    LineListElem<T> *ptr = list.start;
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

// Добавил

// Замыкает список в кольцо
template <class T>
void LineList<T>::makeCircular()
{
    // Присваиваем ссылку на start последнему элементу
    if (start && last)
        last->next = start;
}

// Размыкает список
template <class T>
void LineList<T>::breakCircular()
{
    if (!start)
        return;
    // Присваиваем 0 last->next
    if (last && last->next == start)
        last->next = nullptr;
}

// Иосиф Флавий
int Iosif_Flavia(int n, int k)
{
    if (n <= 0)
        return -1;
    if (n == 1)
        return 1;

    LineList<int> list;

    // Заполнение списка
    list.insertFirst(1);
    LineListElem<int> *last = list.getStart();
    for (int i = 2; i <= n; ++i)
    {
        list.insertAfter(last, i);
        last = last->getNext();
    }

    // Замыкание
    list.makeCircular();

    LineListElem<int> *current = last;
    int count_n = n;

    // Иосиф
    while (count_n > 1)
    {
        // Делаем k-1 переходов, чтобы встать перед элементом, который нужно удалить
        for (int i = 0; i < k - 1; ++i)
        {
            current = current->getNext();
        }

        // Удаляем следующий элемент
        list.deleteAfter(current);
        --count_n;
    }
    // Получение ответа и размыкание списка
    int answer = current->getNext()->getData();
    list.breakCircular();
    return answer;
}

template class LineListElem<int>;
template class LineList<int>;
template ostream &operator<<(ostream &, const LineList<int> &);