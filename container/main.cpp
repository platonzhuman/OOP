#include "array.h"
#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;

int main(void)
{
    setlocale(LC_ALL, "Russian");
    // Array arr(4);
    // for (int i=0; i<4; i++)
    //     arr.insert(i+1);
    // cout<<arr<<endl;
    // for (int i=0; i<8; i+=2)
    //     arr.insert(10+i,i);
    // cout<<arr<<endl;
    // for (int i=1; i<8; i+=2)
    //     arr[i]=20+i;
    // cout<<arr<<endl;
    // for (int i=6; i>=0; i-=3)
    //     arr.remove(i);
    // cout<<arr<<endl;

    // IOSIV

    cout << "WELCOME IOSIV TASK" << endl;
    const int m_N[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    const int num_test = sizeof(m_N) / sizeof(m_N[0]);
    const int K = 2;

    for (int i = 0; i < num_test; ++i)
    {
        int N = m_N[i];
        try
        {
            {
                auto start = high_resolution_clock::now();

                int result = iosiv(N, K);

                auto end = high_resolution_clock::now();

                auto time_prov = duration_cast<microseconds>(end - start);

                cout << "N = " << N
                    << ", result = " << result
                    << ", time = " << time_prov.count() / 1000.0 << endl;

            }
        }
        catch(const ArrayException& e)
        {
            cerr << e.what() << '\n';
        }
        
    }
    return 0;
}