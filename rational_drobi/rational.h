#include <iostream>
using namespace std;
class Rational
{
    void simplify();

public:
    // Числитель
    int numer;
    // Знаменатель (>=1)
    int denom;
    Rational();
    Rational(int numer);
    Rational(int n, int d);
    
    Rational &operator+=(const Rational &r);
    Rational &operator-=(const Rational &r);
    Rational operator+(const Rational &r) const;

    Rational operator-() const;
    Rational &operator++();   // префикс
    Rational operator++(int); // постфикс
    bool operator==(const Rational &r) const;
    bool operator!=(const Rational &r) const;
    operator int() const;
    operator double() const;
    friend istream &operator>>(istream &in, Rational &r);
    friend ostream &operator<<(ostream &out, const Rational &r);

    Rational &operator*=(const Rational& r);
    Rational operator/(const Rational& r) const;

    // kvadrat uravnenie
    friend Rational operator*(int i, const Rational& j);
    Rational operator-(const Rational& r) const;
    Rational operator*(const Rational& r) const;
    static void kvadrat(const Rational& a, const Rational& b, const Rational& c);
};