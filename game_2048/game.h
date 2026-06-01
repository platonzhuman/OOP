#pragma once
#include <vector>
#include <utility>
#include <string>

using namespace std;

class board
{
private:
    int grid[4][4];
    int score;

    vector<pair<int, int>> get_empty_cells(); // список пустых клеток
    void add_random_tile(); //вставка случайние 2 и 4 
    string get_color(int val); 

    vector<int> shift_line(vector<int> line); // сдвиг одной строки

public:
    board(); // обнуление 

    void display(); // вывод поля
    int getscore(); // вернуть счет

    bool move(char dir); // вернет true при изменении

    bool is_won(); // есть лм 2048
    bool is_lost(); // нет ходов
};

class game
{
private:
    board b;

    char get_input();

public:
    void run();
};

