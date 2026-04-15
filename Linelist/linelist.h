#include <iostream>
using namespace std;

template <class T>
class LineListElem
{
    T data;
    LineListElem *next;

public:
    LineListElem(const T &adata, LineListElem *anext);
    const T &getData() const;
    LineListElem *getNext();
    template <class U> friend class LineList;
};

template <class T>
class LineList
{
    LineListElem<T> *start;
    LineList(const LineList &list);
    LineList &operator=(const LineList &list);

public:
    LineList();
    ~LineList();
    LineListElem<T> *getStart();
    void deleteFirst();
    void deleteAfter(LineListElem<T> *ptr);
    void insertFirst(const T &data);
    void insertAfter(LineListElem<T> *ptr, const T &data);
    T iosev(int k);
    template <class U>
    friend ostream &operator<<(ostream &out, const LineList<U> &list);
};

class LineListException : public exception
{
public:
    const char *what() const noexcept override
    {
        return "LineList operation error";
    }
};