#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>        
#include "moon_data_time.h"
using namespace std;

int main() {
    string date;
    cout << "дд.мм.гггг: ";
    cin >> date;
    
    // start ckeck time
    clock_t start = clock();
    
    int d = stoi(date.substr(0,2));
    int m = stoi(date.substr(3,2));
    int y = stoi(date.substr(6,4));
    
    char path[64];
    sprintf(path, "Moon/moon%04d.dat", y);
    
    FILE* f = fopen(path, "r");
    if (!f) {
        cout << "не открылось" << endl;
        return 1;
    }
    
    printMoonEvents(f, date, y, m, d);
    fclose(f);
    
    // stop check time
    clock_t end = clock();
    
    // time in seconde
    double seconds = double(end - start) / CLOCKS_PER_SEC;
    cout << "\nВремя работы: " << seconds << " сек" << endl;
    
    return 0;
}