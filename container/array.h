#include <iostream>
#include <string>
using namespace std;
const int DEFAULT_CAPACITY = 10;

class ArrayException
{
    string message;

public:
    // Конструктор
    ArrayException(const string &msg = "Array error");
    // Текст ошибки
    const char *what() const;
};
class Array
{
    // Хранилище элементов
    int *ptr;
    // Размеры
    int size, capacity;
    bool isFail;

public:
    // Индексация
    int &operator[](int index);
    // Вставка элемента
    void insert(int elem, int index);
    // Вставка элемента в конец массива
    void insert(int elem);
    // Удаление элемента
    void remove(int index);
    // конструктор
    explicit Array(int startCapacity = DEFAULT_CAPACITY);

    // деструктор
    ~Array();

    // конструктор копирования
    Array(const Array &arr);

    // оператор присваивания
    Array &operator=(const Array &arr);

    // получение элемента с заданным индексом
    int get(int index) const;
    // установка значения с заданным индексом
    int set(int index, int elem);

    // форма пригодная только для чтения
    int operator[](int index) const;

    // Варианты обработки ошибочных ситуаций
    bool fail();
    // Увеличение предельного размера
    void increaseCapacity(int newCapacity);
    // Получение размера
    // Вывод массива в поток
    int getSize() const;
    friend ostream &operator<<(ostream &out,
                               const Array &arr);
};

int iosiv(int N, int K);