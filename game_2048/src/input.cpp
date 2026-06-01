#include "input.h"
#include <termios.h> // для tcgetattr / tcsetattr (для переведения в сырой режим)
#include <unistd.h> // для STDIN_FILENO
#include <cstdio> // для getchar

// читаем одну клавишу, стрелки переводим в u / d / l / r
char input_handler::get_input()
{
    struct termios old_t, new_t;
    tcgetattr(STDIN_FILENO, &old_t);

    new_t = old_t;
    new_t.c_lflag &= ~(ICANON | ECHO); // включаем буфер и пропускаем ентер
    tcsetattr(STDIN_FILENO, TCSANOW, &new_t);

    char ch = getchar(); // ждем символ с клавиатуры и возращает его 

    if (ch == '\033')
    {
        getchar(); // пропускаем '['
        char arrow = getchar(); // берем букву
        tcsetattr(STDIN_FILENO, TCSANOW, &old_t);

        switch (arrow)
        {
            case 'A': return 'u';
            case 'B': return 'd';
            case 'C': return 'r';
            case 'D': return 'l';
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
    return ch;
}

// STDIN_FILENO - константа, которая говорит с чем мы работает по умолчанию клавиатура

// TCSANOW - флаг чтобы применить настройки терминала сейчас