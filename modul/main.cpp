#include "file.h" // заголовочный файл
#include "search.h"
#include "geometry.h"
#include <iostream>
#include <locale.h>
using namespace std;

int main(int argc, char** argv){
    setlocale(LC_ALL, "Russian");
    if (argc<3){
        cout<<"Использование: Triangle.exe inf.txt outf.txt"<<endl;
        return -1;
    }
    const char* inFileName = argv[1];
    const char* outFileName = argv[2];
    int pointNum = countPoints(inFileName);
    if(pointNum<0){
        cout<<"Файл не найден"<<endl;
        return -2;
    }
    else if(pointNum < 4){
        cout<<"Файл содержит мало точек"<<endl;
        return -3;
    }
    Point* pointArray = new Point[pointNum];
    if(!readPoints(inFileName, pointArray, pointNum)){
        cout<<"Неверный формат файла"<<endl;
        return -3;
    }
    const int maxTrNum = 3;
    Triangle trArray[maxTrNum];
    searchLargestTriangles(pointArray, pointNum, trArray, maxTrNum);
    if(!writeTriangles(outFileName, trArray, maxTrNum)){
        cout<<"Не удалось открыть файл для записи"<<endl;
        return -4;
    }
    cout<<"Программа успешно завершена"<<endl;
    delete[] pointArray;
    return 0;
} 