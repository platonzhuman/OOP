#include "function.h"
#include <iostream>

using namespace std;

int main() {
    double a = 0.5, b = 3.0, x = 2.0;

    Parabola p(2, -3, 1);
    Hyperbola h(4, 0.5);
    Exponenta e(2, 0.3, -1);

    Function* f[] = { &p, &h, &e };

    for (int i = 0; i < 3; i++) {
        f[i]->printResult(x);
        cout << "Произв: " << f[i]->differentiate(x) << endl;
        cout << "Мин x=" << f[i]->findMin(a, b) << " макс x=" << f[i]->findMax(a, b) << endl;
        cout << "Интеграл: " << f[i]->integrate(a, b) << "\n---\n";
    }
    return 0;
}