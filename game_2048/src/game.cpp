#include "game.h"
#include <iostream>
using namespace std;

// главный цикл — рисуем, проверяем победу/проигрыш, принимаем ход
void game::run()
{
    while (true)
    {
        r.display(b);

        if (b.is_won())
        {
            cout << "\033[1;32m YOU WIN! (SCORE = " << b.getscore() << ")\033[0m\n";
            cout << "Ещё раз? нажми y\n";
            char c = inp.get_input();
            if (c != 'y') break; // если y то можем продолжить дальше
        }

        if (b.is_lost())
        {
            cout << "\033[1;31m YOU LOSER! (SCORE = " << b.getscore() << ")\033[0m\n";
            cout << "Нажми любую клавишу...\n";
            inp.get_input();
            break;
        }

        char dir = inp.get_input();
        if (dir == 'q') break;

        b.move(dir);
    }
}
