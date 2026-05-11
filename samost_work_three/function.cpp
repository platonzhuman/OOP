#include "function.h"
#include <iostream>
using namespace std;

// ================= function ================

// вывод результат
void Function::printResult(double x) const 
{
    cout << "f(" <<x<<") =  " << value(x) << endl;
}


// нахождение минимума
double Function::findMin(double a, double b, double eps) const 
{
    const double zol = (1 + sqrt(5)) / 2;// золотое сечение 
    double c = b - (b - a) / zol; //пробная точка по идее от правого края
    double d = a + (b - a) / zol; // от левого края
    while ((b - a) > eps)
    {
        if(value(c) < value(d))
        {
            b = d;
        }
        else
        {
            a = c;
        }
        c = b - (b - a) / zol;
        d = a + (b - a) / zol;
    }
    return (a + b) / 2;
}


//нахождение максимума
double Function::findMax(double a, double b, double eps) const {
    // находим через поиск минимума от -f(x)
    const double zol = (1 + sqrt(5)) / 2;
    double c = b - (b - a) / zol;
    double d = a + (b - a) / zol;
    while ((b - a) > eps) {
        if (value(c) > value(d)) {
            b = d;
        } else {
            a = c;
        }
        c = b - (b - a) / zol;
        d = a + (b - a) / zol;
    }
    return (a + b) / 2;
}

// интегрируем методов трапеции - делим на кучу маленьких кусков
double Function::integrate(double a, double b, double eps) const {
    int n = 1000; // кол отрезков делим график
    double h = (b - a) / n; // ширина кускф = шаг 
    double sum = 0;

    for (int i = 0; i < n; i++) {
        double x1 = a + i * h;     // левый край кус
        double x2 = a + (i + 1) * h; // правый
        
        // площадь
        sum += (value(x1) + value(x2)) / 2.0 * h;
    }

    return sum;
}

// угол наклона в точке x
double Function::differentiate(double x, double eps) const {
    double h = sqrt(eps); // чтобы не глучило
    return (value(x + h) - value(x - h)) / (2 * h);
}


// ================= parabola ===============

Parabola::Parabola(double a, double b, double c) : A(a), B(b), C(c) {} // сохраняем значения переменных в приват

double Parabola::value(double x) const {
    return A * x * x + B * x + C;
}

void Parabola::printResult(double x) const {
    cout << "парабола: f(x) = " << A << "*x^2 + " << B << "*x + " << C
              << " -> f(" << x << ") = " << value(x) << endl;
}

// ================= hyperbola ===============
Hyperbola::Hyperbola(double a, double b) : A(a), B(b) {}

double Hyperbola::value(double x) const {
    if (x == 0) {
        cerr << "ERRORE == гипербола не определена" << endl;
        return NAN;
    }
    return A / x + B;
}

void Hyperbola::printResult(double x) const {
    cout << "гипербола: f(x) = " << A << "/x + " << B
              << " -> f(" << x << ") = " << value(x) << endl;
}

// ================= exponenta ===============
Exponenta::Exponenta(double a, double b, double c) : A(a), B(b), C(c) {}

double Exponenta::value(double x) const {
    return A * exp(B * x) + C;
}

void Exponenta::printResult(double x) const {
    cout << "экспонента: f(x) = " << A << "*exp(" << B << "*x) + " << C
              << " -> f(" << x << ") = " << value(x) << endl;
}