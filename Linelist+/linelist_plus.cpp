#include "linelist_plus.h"
#include <iostream>
using namespace std;

// Тут мы реализуем методы элементов списка 
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

// тут мы реализуем методы списка

// Удаляем самый первый элемент
template <class T>
void LineList<T>::deleteFirst()
{
    if (start)
    {
        LineListElem<T>* temp = start->next;
        delete start;
        start = temp;   // теперь начало – бывший второй элемент == nullptr
    }
    else throw LineListException();   // нельзя удалить из пустого списка
}

// пустой конструктор
template <class T>
LineList<T>::LineList()
{
    start = 0;
}

// деструктор  = пока есть элементы, удаляем с первого
template <class T>
LineList<T>::~LineList()
{
    while (start)
        deleteFirst();
}

// вставка в начало. Работает по принципу его next = старый start
template <class T>
void LineList<T>::insertFirst(const T& data)
{
    LineListElem<T>* second = start;
    start = new LineListElem<T>(data, second);
}

// удаление элемента, который идёт после ptr
template <class T>
void LineList<T>::deleteAfter(LineListElem<T>* ptr)
{
    if (ptr && ptr->next)   // если есть сам ptr, и следующий за ним
    {
        LineListElem<T>* temp = ptr->next;
        ptr->next = ptr->next->next;   // перекидываем связь через удаляемый
        delete temp;
    }
    else throw LineListException();
}

// вставка нового элемента после ptr
template <class T>
void LineList<T>::insertAfter(LineListElem<T>* ptr, const T& data)
{
    if (ptr)
    {
        LineListElem<T>* temp = ptr->next;
        ptr->next = new LineListElem<T>(data, temp);   // вставляем между ptr и temp
    }
}

// возвращает начало списка
template <class T>
LineListElem<T>* LineList<T>::getStart()
{
    return start;
}

// Вывод списка в терминал
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
    // проверка на пустой список
    if (start == nullptr)
        throw LineListException();
    
    // ищет последний элемент и считает общее количество этих элеметов
    LineListElem<T>* last = start;
    int count = 1;
    while (last->next != nullptr)
    {
        last = last->next;
        ++count;
    }
    // Зымыкание, когда последний элемент указывает на первый
    last->next = start;

    // Двигаемся по кругу K шагами удаляя жлементы

    LineListElem<T>* prew = last;   // элемент перед тем, кого будем удалять
    LineListElem<T>* curent = start; // удаляемый элемент

    while(count > 1)  
    {
        // этот цикл делает k - 1 шагов вперед
        for (int i = 0; i < k - 1 ; ++i)
        {
            prew = curent;
            curent = curent->next;
        }
        // перебрасываем указатель на след элемент и удаляем curent
        prew->next = curent->next;
        delete curent;

        // теперь след элем стал текущим
        curent = prew->next;
        --count; 
    }

    // результат в виде одного числа 
    T result = curent->data;

    // Тут происходит разрыв кольца
    curent->next = nullptr;
    start = curent;

    return result;
}


// тут все для linelist<int>

// создают все методы класса 
template class LineListElem<int>;
template class LineList<int>;


// создает конкретную версию оператора
template ostream& operator<<(ostream& out, const LineList<int>& list);