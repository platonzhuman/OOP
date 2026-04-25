#include <iostream>
using namespace std;

// Элемент списка (узел)
template <class T>
class LineListElem
{
    T data;               // значение, которое хранится в узле
    LineListElem *next;   // указатель на следующий элемент

public:
    // конструктор,который запоминаем данные и указатель на следующий
    LineListElem(const T &adata, LineListElem *anext);
    
    // возвращаем константную ссылку на данныедля чтения
    const T &getData() const;
    
    // возвращаем указатель на следующий элемент
    LineListElem *getNext();
    
    // делаем так, чтобы он мог менять поля напрямую
    template <class U> friend class LineList;
};

// Сам линейный список
template <class T>
class LineList
{
    LineListElem<T> *start;   // указатель на первый элемент
    
    // Запрещает копирование и присваивание 
    LineList(const LineList &list);
    LineList &operator=(const LineList &list);

public:
    LineList();                                 // пустой конструктор 
    ~LineList();                                // деструктор (удалит все)
    LineListElem<T> *getStart();                // получить указатель на начало
    void deleteFirst();                         // удалить первый элемент
    void deleteAfter(LineListElem<T> *ptr);     // удалить элемент после ptr
    void insertFirst(const T &data);            // вставить в начало
    void insertAfter(LineListElem<T> *ptr, const T &data); // вставить после ptr
    
    T iosev(int k);   // задача ioseva
    
    // Дружественная функция для вывода списка в терминал красиво
    template <class U>
    friend ostream &operator<<(ostream &out, const LineList<U> &list);
};

// Простое исключение для ошибок списка
class LineListException : public exception
{
public:
    const char *what() const noexcept override
    {
        return "LineList operation error";
    }
};