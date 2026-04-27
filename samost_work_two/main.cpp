#include "four.h"
#include <iostream>
#include <locale.h>   
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Field field(true);   // true -> start red

    while (!field.isOver()) {
        field.print();
        cout << "GO -> " 
                  << (field.isRedTurnNow() ? "RED" : "YELOW")
                  << " player. Write number column (1..7): ";
        int col;
        cin >> col;
        
        if (cin.fail() || !field.makeTurn(col)) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << "ERROR! Please repeat again ^_^\n";
            continue;
        }
    }

    field.print();
    field.printResult();

    return 0;
}