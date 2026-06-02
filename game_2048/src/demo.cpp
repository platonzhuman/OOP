#include "demo.h"
#include <iostream>
#include <unistd.h> // для usleep
using namespace std;

// пробуем направления по порядку — берём первое которое что-то меняет
char demo::get_move()
{
    const char dirs[] = {'l', 'd', 'r', 'u'};

    for (char dir : dirs)
    {
        board copy = b; // копируем поле 
        if (copy.move(dir)) return dir; // если ход изменил копию, значит он действенный
    }

    return 'q'; // ходов нет
}

// демо цикл рисуем, проверяем победу, проигрыш, ходим, ждём
void demo::run()
{
    while (true)
    {
        r.display(b);

        if (b.is_won())
        {
            cout << "\033[1;32m AI WIN! (SCORE = " << b.getscore() << ")\033[0m\n";
            break;
        }
        if (b.is_lost())
        {
            cout << "\033[1;31m AI LOSER! (SCORE = " << b.getscore() << ")\033[0m\n";
            break;
        }

        char dir = get_move();
        if (dir == 'q') break;

        // показываем куда ходим
        string dir_name;
        switch (dir)
        {
            case 'l': dir_name = "LEFT";  break;
            case 'r': dir_name = "RIGHT"; break;
            case 'u': dir_name = "UP";    break;
            case 'd': dir_name = "DOWN";  break;
        }
        cout << "AI: " << dir_name << "\n";

        b.move(dir);
        usleep(2000000); // пауза по идее 3 секунды 
    }
}
