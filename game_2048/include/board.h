#pragma once
#include <vector>
#include <utility> // для pair - структура котора яхранит два значения вместе
using namespace std;

class board {
private:
    int grid[4][4];
    int score;

    vector<pair<int, int>> get_empty_cells(); // все пустые координаты клеток
    void add_random_tile();                   // кинуть 2 или 4 в случайную клетку
    vector<int> shift_line(vector<int> line); // сдвиг строки влево

public:
    board();                          // обнулить сетку, поставить 2 плитки

    int get_cell(int i, int j) const; // значение клетки для рендерера
    int getscore() const;             // вернуть счёт

    bool move(char dir);              // ход, true если поле изменилось
    bool is_won();                    // есть ли 2048
    bool is_lost();                   // нет ходов — конец
};
