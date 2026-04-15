#include <iostream>
#include <string>
#include "data_time.h"
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    string s1, s2;
    int days_to_add;

    cout << "--- WELCOME DATA_TIME PROJECT ---" << endl;
    cout << "введите первую дату (ГГГГ-ММ-ДД или ГГГГ-ММ-ДДTчч:мм:сс): ";
    cin >> s1;
    cout << "введите вторую дату (ГГГГ-ММ-ДД или ГГГГ-ММ-ДДTчч:мм:сс): ";
    cin >> s2;

    Datatime d1(s1);
    Datatime d2(s2); 

    cout << "\n--- проверка работы методов ---" << endl;
    
    cout << "первая дата: " << d1 << endl;
    cout << "вторая дата: " << d2 << endl;

    double diff = d1 - d2;
    cout << "разица между ними в днях: " << diff << endl;

    int w = d1.week();
    if (w != -1)
        cout << "день недели для первой даты (0-Пн, 6-Вс): " << w << endl;
    else
        cout << "день недели: невозможно определить (ошибка даты)" << endl;
    cout << "\nсколько целых дней прибавить к первой дате? ";
    if (!(cin >> days_to_add)) {
        cout << "ошибка вода числа!" << endl;
        return 1;
    }
    
    Datatime d3 = d1 + days_to_add;
    cout << "результат сложения: " << d3 << endl;

    cout << "\n--- сравнение ---" << endl;
    if (d1 > d2) {
        cout << "Первая дата ПОЗЖЕ второй" << endl;
    } else if (d1 == d2) {
        cout << "Даты и время ПОЛНОСТЬЮ СОВПАДАЮТ" << endl;
    } else {
        cout << "Первая дата РАНЬШЕ второй" << endl;
    }

    return 0;
}
