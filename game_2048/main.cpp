#include "game.h"
#include "demo.h"
#include <iostream>
using namespace std;

int main()
{
    char c;
    cout << "1 - играть  |  2 - демо режим\n";
    cin >> c;

    if (c == '2') {
        demo d;
        d.run();
    } else {
        game g;
        g.run();
    }

    return 0;
}
