#include "linelist_plus.h"
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

int main()
{
    const int k = 2;
    int n[7] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    double time[7];
    int result[7];
    for (int i = 0; i < 7; i++)
    {
        auto start = high_resolution_clock::now();
        result[i] = Iosif_Flavia(n[i], k);
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        time[i] = elapsed.count();

        cout << "n = " << n[i]
             << ", result = " << result[i]
             << ", time = " << time[i] << " sek" << endl;
    }
    return 0;
}