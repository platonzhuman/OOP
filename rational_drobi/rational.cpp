#include "rational.h"
#include <iostream>
#include <cmath>
using namespace std;

Rational::Rational() : numer(0), denom(1) {}

Rational::Rational(int n, int d) : numer(n), denom(d) {
    simplify();
}

Rational::Rational(int numer) : numer(numer), denom(1) {
    simplify();
}

// Оператор Добавление
Rational &Rational::operator+=(const Rational &r)
{
    numer = (numer * r.denom + denom * r.numer);
    denom *= r.denom;
    simplify(); // упрощение
    return *this;
}
// оператор уменьшения
Rational &Rational::operator-=(const Rational &r)
{
    return (*this += (-r));
}

// Оператор сложения
Rational Rational::operator+(const Rational &r) const
{
    Rational res(*this);
    return res += r;
}
// Оператор умножения 
Rational &Rational::operator*=(const Rational& r)
{
    numer*=r.numer;
    denom*= r.denom;
    simplify();
    return *this;
}

//оператор деления 
Rational Rational::operator/(const Rational& r) const {
    return Rational(numer * r.denom, denom * r.numer);
}

// Упрощение
void Rational::simplify()
{
    if (denom < 0)
    {
        numer = -numer;
        denom = -denom;
    }
    for (int i = 2; i <= abs(denom) && i <= abs(numer); i++)
        if (numer % i == 0 && denom % i == 0)
        {
            numer /= i;
            denom /= i;
            i--;
        }
}

// Оператор отрицания
Rational Rational::operator-() const
{
    Rational r(-numer, denom);
    return r;
}

// префикс
Rational &Rational::operator++()
{
    numer += denom;
    return *this;
}

// постфикс
Rational Rational::operator++(int)
{
    Rational r(*this);
    numer += denom;
    return r;
}

// ==
bool Rational::operator==(const Rational &r) const
{
    return (numer == r.numer) && (denom == r.denom);
}

// !=
bool Rational::operator!=(const Rational &r) const
{
    return !(*this == r);
}

// int
Rational::operator int() const
{
    return numer / denom;
}

// double
Rational::operator double() const
{
    return ((double)numer) / denom;
}

istream &operator>>(istream &in, Rational &r)
{
    in >> r.numer >> r.denom;
    return in;
}
ostream &operator<<(ostream &out, const Rational &r)
{
    out << r.numer << "/" << r.denom;
    return out;
}

// a**2 +- 2ab + b**2
Rational Rational::operator-(const Rational& r) const
{
    Rational res(*this);
    res -= r;
    return res;
}

Rational Rational::operator*(const Rational& r) const 
{
    Rational res(*this);
    res *= r;
    return res;
}
//=== kvadrat uravnenie ===


Rational operator*(int i, const Rational& j) 
{
    return Rational(i * j.numer, j.denom);
}

void Rational::kvadrat(const Rational& a, const Rational& b, const Rational& c) {
    cout << "Uravnenie: (" << a << ")x^2 + (" << b << ")x + (" << c << ") = 0" << endl;

    Rational Dis = (b * b) - (4 * a * c);
    
    double d = Dis; 
    
    if (d < 0) {
        cout << "Net realnih korney" << endl;
        return;
    }

    double a_d = a;
    double b_d = b;
    
    double sqrtD = sqrt(d);          
      
    Rational x1 = (-b_d + sqrtD) / (2 * a_d);
    Rational x2 = (-b_d - sqrtD) / (2 * a_d);

    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
}