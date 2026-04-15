#include "geometry.h"
#include <cmath>

double calcDistance(const Point& pa, const Point& pb) {
    double dx = pb.x - pa.x;
    double dy = pb.y - pa.y;
    return sqrt(dx*dx + dy*dy);
}

double calcAreaBySides(double a, double b, double c) {
    double p2 = (a + b + c) / 2.0;
    // проверка на вырожденный треугольник
    if (p2 <= 0.0 || p2 <= a || p2 <= b || p2 <= c)
        return 0.0;
    return sqrt(p2 * (p2 - a) * (p2 - b) * (p2 - c));
}

double calcAreaByPoints(double xa, double ya,
                        double xb, double yb,
                        double xc, double yc) {
    double ab = sqrt((xb - xa)*(xb - xa) + (yb - ya)*(yb - ya));
    double bc = sqrt((xc - xb)*(xc - xb) + (yc - yb)*(yc - yb));
    double ca = sqrt((xa - xc)*(xa - xc) + (ya - yc)*(ya - yc));
    return calcAreaBySides(ab, bc, ca);
}


double calcTriangleArea(Triangle& tr) {
    Point* v = tr.vertexes;
    double a = calcDistance(v[0], v[1]);
    double b = calcDistance(v[1], v[2]);
    double c = calcDistance(v[2], v[0]);
    return tr.area = calcAreaBySides(a, b, c);
}