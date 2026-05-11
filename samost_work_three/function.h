#include <iostream>
#include <cmath>

// это абстрактный клас у нас
class Function {
public:
    // вычисление функции f = y(x)
    virtual double value(double x) const = 0;

    // вывод результат в терминал
    virtual void printResult(double x) const;

    // поиск мин на интервале
    virtual double findMin(double a, double b, double eps = 1e-6) const;

    // поиск макс на интервале
    virtual double findMax(double a, double b, double eps = 1e-6) const;

    // Численное интегрирование (метод трапеций)
    virtual double integrate(double a, double b, double eps = 1e-6) const;

    // Численное дифференцирование (центральная разность)
    virtual double differentiate(double x, double eps = 1e-6) const;

    virtual ~Function() {} // Виртуальный деструктор
};

//parabola
class Parabola : public Function {
private:
    double A, B, C;
public:
    Parabola(double a = 1, double b = 0, double c = 0);
    double value(double x) const override;
    void printResult(double x) const override;
};


//hyberbola
class Hyperbola : public Function {
private:
    double A, B;
public:
    Hyperbola(double a = 1, double b = 0);
    double value(double x) const override;
    void printResult(double x) const override;
};

// exponenta
class Exponenta : public Function {
private:
    double A, B, C;
public:
    Exponenta(double a = 1, double b = 1, double c = 0);
    double value(double x) const override;
    void printResult(double x) const override;
};