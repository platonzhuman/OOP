#include "linelist.h"
#include <iostream>
#include <locale.h>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

void iosev()
{
    int k = 2;
    int N[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int num_tests = sizeof(N) / sizeof(N[0]);
    cout << "N\tОтвет\tВремя (сек)\n";

    for (int i = 0; i < num_tests; ++i)
    {
        int n = N[i];
        LineList<int> list;
        list.insertFirst(n);
        for (int i = n - 1; i >= 1; --i)
            list.insertFirst(i);

        auto start = high_resolution_clock::now();
        int result = list.iosev(k);
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;

        cout << n << "\t" << result << "\t"
             << fixed << setprecision(6) << elapsed.count() << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    LineList<int> list;
    cout << "Начало: " << list << endl;

    list.insertFirst(10);
    LineListElem<int>* ptr = list.getStart();
    list.insertAfter(ptr, 15);
    list.insertAfter(ptr->getNext(), 12);
    list.insertFirst(7);

    cout << "Шаг 1: " << list << endl;

    int sum = 0;
    for (LineListElem<int>* it = list.getStart(); it; it = it->getNext())
        sum += it->getData();

    cout << "Сумма элементов = " << sum << endl;

    cout << "\n=== IOSIV ===\n";
    iosev();

    return 0;
}