#include "game.h"
#include <iostream>
#include <cstdlib> // for rand()
#include <ctime> 
#include <string>
#include <termios.h> // для сырого режима терминала
#include <unistd.h> // для STDIN_FILENO

using namespace std;


// выстраивание сетки и обнуление счета
board::board()
{
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) grid[i][j] = 0;   

    score = 0;

    srand(time(0)); // инициализация генератора случайных чисел 
    add_random_tile(); // первая стартовая плитка
    add_random_tile(); //  вторая стартовая плитка
}

// вывод счета
int board::getscore()
{
    return score;
}

vector<pair<int, int>> board::get_empty_cells()
{
    vector<pair<int, int>> empty;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == 0)
                empty.push_back({i, j});  // запоминаем координаты пустой клетки

    return empty;
}

void board::add_random_tile()
{
    vector<pair<int, int>> empty = get_empty_cells();

    if (empty.empty()) return; // если клетка заполнена, ничего не делаем

    // случайная пустая клетка
    int idx = rand() % empty.size();
    int row = empty[idx].first;
    int col = empty[idx].second;

    // расчет вероятности 90% - 2 , 10% - 4
    grid[row][col] = (rand() % 10 == 0) ? 4 : 2;

}

vector<int> board::shift_line(vector<int> line)
{
    // собираем все ненулевые числа в вектор
    vector<int> nums;
    for (int val : line)
        if (val != 0) nums.push_back(val);
    
    // проходим слева, сливаем соседние
    for (int i = 0; i < (int)nums.size() - 1; i++)
    {
        if(nums[i] == nums[i + 1])
        {
            nums[i] *= 2;
            score += nums[i];
            nums.erase(nums.begin() + i + 1); // удаляем правую, т.к влилась ("erase - удаляет элемент по итератору")
        }
    }

    //  добиваем нулями до длины 4
    while ((int)nums.size() < 4) nums.push_back(0);

    return nums;  
}

bool board::move(char dir)
{
    // сохраняем поле для сравнения
    int old[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            old[i][j] = grid[i][j];
    
    if (dir == 'l')
    {
        for (int i = 0; i < 4; i++)
        {
            // для каждой строки: вытащить в вектор - shift_line - положить обратно
            vector<int> row = {grid[i][0], grid[i][1], grid[i][2], grid[i][3]}; 
            row = shift_line(row);
            for (int j = 0; j < 4; j++) grid[i][j] = row[j];
        }
    }
    else if (dir == 'r')
    {
        // вправо = развернуть строку - shift_line - развернуть обратно
        for (int i = 0; i < 4; i++)
        {
            vector<int> row = {grid[i][3], grid[i][2], grid[i][1], grid[i][0]};
            row = shift_line(row);
            grid[i][0] = row[3]; grid[i][1] = row[2];
            grid[i][2] = row[1]; grid[i][3] = row[0];
        }
    }

    else if (dir == 'u')
    {
        // вверх = работаем по столбцам сверху вниз
        for (int j = 0; j < 4; j++)
        {
            vector<int> col = {grid[0][j], grid[1][j], grid[2][j], grid[3][j]};
            col = shift_line(col);
            for (int i = 0; i < 4; i++) grid[i][j] = col[i];
        }
    }
    else if (dir == 'd') {
        // вниз = столбец снизу вверх (разворачиваем)
        for (int j = 0; j < 4; j++) {
            vector<int> col = {grid[3][j], grid[2][j], grid[1][j], grid[0][j]};
            col = shift_line(col);
            grid[0][j] = col[3]; grid[1][j] = col[2];
            grid[2][j] = col[1]; grid[3][j] = col[0];
        }
    }

    // проверка на то, изменилось ли поле
    bool changed = false;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) 
            if (grid[i][j] != old[i][j]) changed = true;
    //если изменилось, кидаем новую плитку
    if (changed) add_random_tile();

    return changed;
}

// проверка на победу
bool board::is_won()
{
    for (int i = 0; i< 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == 2048) return true;
    return false;
}

// проверка на возможности ходов
bool board::is_lost() {
    // проверка на наличие пустых клеток
    if (!get_empty_cells().empty()) return false;

    //проверка соседей по горизонтале и вертикале
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            // сосед справа
            if (j + 1 < 4 && grid[i][j] == grid[i][j + 1]) return false;

            // сосед снизу
            if (i + 1 < 4 && grid[i][j] == grid[i + 1][j]) return false;
        }
    }

    return true;
}



char game::get_input()
{
    // сохраняем текущие настройки терминала
    struct termios old_t, new_t;
    tcgetattr(STDIN_FILENO, &old_t);

    // включаем сырой режим без буфера ...
    new_t = old_t;
    new_t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_t);

    char ch = getchar();

    if (ch == '\033'){ // пришла стрелка
        getchar(); // пропускаем "["
        char arrow = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &old_t); // восстанавливаем терминал

        switch(arrow) // стрелки 
        {
            case 'A': return 'u';   // вверх
            case 'B': return 'd';   //  вниз
            case 'C': return 'r';   // вправо
            case 'D': return 'l';   //  влево
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old_t); // восстанавливаем тарминал
    return ch; // вернули обычный символ

}

void game::run()
{
    while (true)
    {
        b.display();

        if (b.is_won())
        {
            cout << "\033[1;32m YOU WIN (SCARE =  " << b.getscore() << ")\033[0m\n";
            cout << "AGAIN ? write y";
            char c = get_input();
            if (c != 'y') break;           
        }
        if (b.is_lost()) {
            cout << "\033[1;31m  YOU LOSER ! (SCARE =  " << b.getscore() << ")\033[0m\n";
            cout << "Click enter ...\n";
            get_input();
            break;
        }

        // читаем ход
        char dir = get_input();
        if (dir == 'q') break;  

        b.move(dir);
    }
}



string board::get_color(int val)
{
    switch(val)
    {
        case 2:    return "\033[1;33m";   // жёлтый
        case 4:    return "\033[1;93m";   // ярко-жёлтый
        case 8:    return "\033[1;31m";   // красный
        case 16:   return "\033[1;91m";   // ярко-красный
        case 32:   return "\033[1;35m";   // фиолетовый
        case 64:   return "\033[1;95m";   // ярко-фиолетовый
        case 128:  return "\033[1;36m";   // голубой
        case 256:  return "\033[1;96m";   // ярко-голубой
        case 512:  return "\033[1;32m";   // зелёный
        case 1024: return "\033[1;92m";   // ярко-зелёный
        case 2048: return "\033[1;94m";   // синий — победа!
        default:   return "\033[1;97m";   // белый     
    }
}


void board::display()
{
    // очищаем экран и переводим курсор в начало
    cout << "\033[2J\033[H";

    // заголовок
    cout << "\033[1m=== 2048 ===\033[0m\n";
    cout << "Счёт: " << score << "\n\n";

    cout << "+-------+-------+-------+-------+\n";

    for (int i = 0; i < 4; i++)
    {
        cout << "|";
        for (int j = 0; j < 4;j++)
        {
            int val = grid[i][j];

            if (val == 0) cout << "       |";
            else{
                string s = to_string(val); // преобразуем число в строку

                int pad = 7 - (int)s.size(); // 7 = ширина ячейки (столько же дефисов в разделителе)
                int left = pad / 2;
                int right = pad - left;

                // выводим цвет + пробелы + число + сброс цвета
                cout << get_color(val);
                cout << string(left, ' ') << s << string(right, ' ');
                cout << "\033[0m" << "|";
            }

        }
        cout << "\n";
        cout << "+-------+-------+-------+-------+\n"; 
    }
    cout << "\n";
    cout << "controls: strelki  |  exit: q";
}