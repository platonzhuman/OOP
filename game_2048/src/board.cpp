#include "board.h"
#include <cstdlib> // для генерации случайных чисел
#include <ctime>
using namespace std;

// обнуляем сетку, счёт и кидаем две стартовые плитки
board::board()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) grid[i][j] = 0;

    score = 0;
    srand(time(0));
    add_random_tile();
    add_random_tile();
}

// отдаём значение клетки — нужно рендереру чтобы рисовать
int board::get_cell(int i, int j) const
{
    return grid[i][j];
}

// вернуть счёт
int board::getscore() const
{
    return score;
}

// собираем координаты всех пустых клеток в вектор
vector<pair<int, int>> board::get_empty_cells()
{
    vector<pair<int, int>> empty;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == 0)
                empty.push_back({i, j}); // добавление в вектор
    return empty;
}

// кидаем 2 или 4 в случайную пустую клетку (90% / 10%)
void board::add_random_tile()
{
    vector<pair<int, int>> empty = get_empty_cells();
    if (empty.empty()) return;

    int idx = rand() % empty.size(); // выбираем случайную ячейку
    int row = empty[idx].first; 
    int col = empty[idx].second;
    // узнав номер строки и столбца 
    grid[row][col] = (rand() % 10 == 0) ? 4 : 2; 
}

// сдвиг одной строки влево — убираем нули, сливаем одинаковые, добиваем нулями
vector<int> board::shift_line(vector<int> line)
{
    vector<int> nums;
    for (int val : line) // пробегаем по val = line[i]
        if (val != 0) nums.push_back(val);

    for (int i = 0; i < (int)nums.size() - 1; i++)
    {
        if (nums[i] == nums[i + 1])
        {
            nums[i] *= 2;
            score += nums[i];
            nums.erase(nums.begin() + i + 1);
        }
    }

    while ((int)nums.size() < 4) nums.push_back(0);
    return nums;
}

// ход в нужную сторону, вернёт true если поле изменилось
bool board::move(char dir)
{
    int old[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            old[i][j] = grid[i][j];

    if (dir == 'l') // тут мы просто вызываем shift line
    {
        for (int i = 0; i < 4; i++)
        {
            vector<int> row = {grid[i][0], grid[i][1], grid[i][2], grid[i][3]};
            row = shift_line(row);
            for (int j = 0; j < 4; j++) grid[i][j] = row[j];
        }
    }
    else if (dir == 'r') // тут нам надо развернуть строку
    {
        for (int i = 0; i < 4; i++)
        {
            vector<int> row = {grid[i][3], grid[i][2], grid[i][1], grid[i][0]};
            row = shift_line(row);
            grid[i][0] = row[3]; grid[i][1] = row[2];
            grid[i][2] = row[1]; grid[i][3] = row[0];
        }
    }
    else if (dir == 'u') // то есть читаем сверху вниз далее shift line  и кладем обратно
    {
        for (int j = 0; j < 4; j++)
        {
            vector<int> col = {grid[0][j], grid[1][j], grid[2][j], grid[3][j]};
            col = shift_line(col);
            for (int i = 0; i < 4; i++) grid[i][j] = col[i];
        }
    }
    else if (dir == 'd') // все то же самое только наоборот по идее
    {
        for (int j = 0; j < 4; j++)
        {
            vector<int> col = {grid[3][j], grid[2][j], grid[1][j], grid[0][j]};
            col = shift_line(col);
            grid[0][j] = col[3]; grid[1][j] = col[2];
            grid[2][j] = col[1]; grid[3][j] = col[0];
        }
    }

    bool changed = false;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] != old[i][j]) changed = true;

    if (changed) add_random_tile();
    return changed;
}

// есть ли на поле 2048
bool board::is_won()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == 2048) return true;
    return false;
}

// нет пустых клеток и нечего слить — конец игры
bool board::is_lost()
{
    // запрашиваем список пустых клеток
    if (!get_empty_cells().empty()) return false;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {   // если хоть один одинаковый сосед, то игра не проиграна
            if (j + 1 < 4 && grid[i][j] == grid[i][j + 1]) return false;
            if (i + 1 < 4 && grid[i][j] == grid[i + 1][j]) return false;
        }

    return true;
}
