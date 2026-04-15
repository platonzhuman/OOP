#ifndef _SEARCH_H
#define _SEARCH_H
#include "geometry.h"
void searchLargestTriangles(const Point* pointArray, int pointNum, Triangle* trArray, int maxTrNum);
void clearTriangle(Triangle& tr);  
void clearPoint(Point& p); 
void findAndInsert(Triangle* trArray, int length, const Triangle& triangle);
#endif