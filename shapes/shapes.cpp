#include "shapes.h"
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

Shape::~Shape() {}

double Circle::calc_area() {
    return 3.14 * radius * radius;
}

double Circle::calc_perimetr() {
    return 3.14 * 2 * radius;
}

void Circle::name() {
    cout << "jrug" << endl;
}

double Ellipse::calc_area() {
    return 3.14 * big_radius * small_radius;
}

double Ellipse::calc_perimetr() {
    // приближённая формула рамануджана точного решения нет
    return 3.14 * (3 * (big_radius + small_radius) - sqrt((3*small_radius + big_radius) * (3*big_radius + small_radius)));
}

void Ellipse::name() {
    cout << "ellips" << endl;
}

double Rectangle::calc_area() {
    // вычисляем ширину и высоту из координат углов
    double a = lower_right.x - upper_left.x;
    double b = upper_left.y - lower_right.y;
    return a * b;
}

double Rectangle::calc_perimetr() {
    double a = lower_right.x - upper_left.x;
    double b = upper_left.y - lower_right.y;
    return 2 * (a + b);
}

void Rectangle::name() {
    cout << "Прямоугольник" << endl;
}

double Triangle::calc_area() {
    // формула через векторное произведение fabs берёт модуль чтоб не было минуса
    return 0.5 * fabs(A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y));
}

double Triangle::calc_perimetr() {
    double AB = sqrt((B.x - A.x)*(B.x - A.x) + (B.y - A.y)*(B.y - A.y));
    double BC = sqrt((C.x - B.x)*(C.x - B.x) + (C.y - B.y)*(C.y - B.y));
    double AC = sqrt((A.x - C.x)*(A.x - C.x) + (A.y - C.y)*(A.y - C.y));
    return AB + BC + AC;
}

void Triangle::name() {
    cout << "treugolnik" << endl;
}

Polygon::Polygon(const string& filename) {
    ifstream file(filename);
    int n;
    file >> n; // первое число в файле это количество точек

    coords.resize(n);
    for (int i = 0; i < n; i++)
        file >> coords[i].x >> coords[i].y;

}

double Polygon::calc_area() {
    double area = 0;

    for (int i = 0; i < coords.size(); i++) {
        // % замыкает индекс чтоб последняя точка соединялась с первой
        int j = (i + 1) % coords.size();
        // формула гаусса для площади произвольного многоугольника
        area += coords[i].x * coords[j].y;
        area -= coords[i].y * coords[j].x;
    }

    // площадь может выйти отрицательной зависит от обхода вершин
    if (area < 0)
        area = -area;

    return 0.5 * area;
}

double Polygon::calc_perimetr() {
    double perimetr = 0;

    for (int i = 0; i < coords.size(); i++) {
        int j = (i + 1) % coords.size();
        perimetr += sqrt((coords[j].x - coords[i].x)*(coords[j].x - coords[i].x) + (coords[j].y - coords[i].y)*(coords[j].y - coords[i].y));
    }

    return perimetr;
}

void Polygon::name() {
    cout << "many ugolnik" << endl;
}