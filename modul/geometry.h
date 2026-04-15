#ifndef _GEOMETRY_H
#define _GEOMETRY_H
#include <iostream>
#include <cmath>
using namespace std;

struct Point{
    double x, y;
};

struct Triangle{
    Point vertexes[3];
    double area;
};
inline bool operator<=(const Triangle& a, const Triangle& b) {
    return a.area <= b.area;
}
double calcDistance(const Point& pa, const Point& pb);
double calcAreaByPoints(double xa, double ya,double xb, double yb,double xc, double yc);
double calcTriangleArea(Triangle& tr);
double calcAreaBySides(double a, double b, double c);
inline ostream& operator<<(ostream& out, const Triangle& tr) {
    for (int i = 0; i < 3; i++)
        out << "(" << tr.vertexes[i].x << "," << tr.vertexes[i].y << ") ";
    out << "area=" << tr.area;
    return out;
}
inline istream& operator>>(istream& in, Point& p) {
    return in >> p.x >> p.y;
}
#endif