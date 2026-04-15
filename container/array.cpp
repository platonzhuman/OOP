#include "array.h"
#include <iostream>
using namespace std;

// Конструктор
ArrayException::ArrayException(const string &msg) : message(msg) {}

// Текст ошибки
const char *ArrayException::what() const { return message.c_str(); }

// конструтор
Array::Array(int startCapacity)
{
    if (startCapacity <= 0)
        capacity = DEFAULT_CAPACITY;
    else
        capacity = startCapacity;
    ptr = new int[capacity];
    size = 0;
}

// деструктор

Array::~Array()
{
    delete[] ptr;
}
// оператор копирования
Array::Array(const Array &arr)
{
    ptr = new int[arr.capacity];
    size = arr.size;
    capacity = arr.capacity;
    for (int i = 0; i < size; i++)
        ptr[i] = arr.ptr[i];
}

// оператор присваивания

Array &Array::operator=(const Array &arr)
{
    if (this == &arr)
        return *this;
    if (capacity != arr.capacity)
    {
        delete[] ptr;
        ptr = new int[arr.capacity];
        capacity = arr.capacity;
    }
    size = arr.size;
    for (int i = 0; i < size; i++)
        ptr[i] = arr.ptr[i];
    return *this;
}

// получение элемента с заданным индексом
int Array::get(int index) const
{
    if (index < 0 || index >= size)
        throw ArrayException("Index out of range in get()");
    return ptr[index];
}

// установка значения с заданным индексом
int Array::set(int index, int elem)
{
    if (index < 0 || index >= size)
        throw ArrayException();
    ptr[index] = elem;
    return elem;
}

// оперраторы индексации
int &Array::operator[](int index)
{
    if (index >= size || index < 0)
        throw ArrayException("Index out of range in operator[]");
    else
        return ptr[index];
}

// Константный оператор индексации
int Array::operator[](int index) const
{
    if (index >= size || index < 0)
        throw ArrayException("Index out of range in const operator[]");
    return ptr[index];
}

// Вставка элемента
void Array::insert(int elem, int index)
{
    if (index < 0 || index > size)
        throw ArrayException("Index out of range in insert");
    if (size == capacity)
        // Закрытая функция, увеличивающая предельный размер
        increaseCapacity(size + 1);
    // Если index==size, этот цикл не выполнится ни разу
    for (int j = size - 1; j >= index; j--)
        ptr[j + 1] = ptr[j];
    size++;
    ptr[index] = elem;
}

// Вставка элемента в конец
void Array::insert(int elem)
{
    insert(elem, size);
}

// Увеличение предельного размера
void Array::increaseCapacity(int newCapacity)
{
    capacity = newCapacity < capacity * 2 ? capacity * 2 : newCapacity;
    int *newPtr = new int[capacity];
    for (int i = 0; i < size; i++)
        newPtr[i] = ptr[i];
    delete[] ptr;
    ptr = newPtr;
}

// Удаление элемента
void Array::remove(int index)
{
    if (index < 0 || index >= size)
        throw ArrayException();
    for (int j = index; j < size - 1; j++)
        ptr[j] = ptr[j + 1];
    ptr[size - 1] = 0;
    size--;
}
// Получение размера
// Вывод массива в поток
int Array::getSize() const
{
    return size;
}
ostream &operator<<(ostream &out,
                    const Array &arr)
{
    out << "Total size: " << arr.size << endl;
    for (int i = 0; i < arr.size; i++)
        out << arr.ptr[i] << endl;
    return out;
}

// IOSIV TASK

int iosiv(int N, int K)
{
    if (N <= 0 || K <= 0)
        throw ArrayException("Your number < 0");
    
    Array arr(N);
    for (int i = 1; i <= N; ++i)
        arr.insert(i);
    int tek_pozition = 0;

    while (arr.getSize() > 1)
    {
        int size = arr.getSize();
        int remot_index = (tek_pozition + K - 1) % size;
        arr.remove(remot_index);
        tek_pozition = remot_index;
    }
    return arr[0];
}