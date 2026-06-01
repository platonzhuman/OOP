#include "renderer.h"
#include "color.h"
#include <iostream>
#include <string>
using namespace std;

// чистим экран и рисуем поле с цветными плитками
void renderer::display(const board& b)
{
    cout << "\033[2J\033[H"; // очищаем экран и перемещаем курсор в левый верзний угол

    cout << "\033[1m=== 2048 ===\033[0m\n"; // включить жирный шрифт и обратнно
    cout << "Счёт: " << b.getscore() << "\n\n";

    cout << "+-------+-------+-------+-------+\n";

    for (int i = 0; i < 4; i++)
    {
        cout << "|";
        for (int j = 0; j < 4; j++)
        {
            int val = b.get_cell(i, j); // получаем значение клетки 

            if (val == 0)
            {
                cout << "       |";
            }
            else
            {
                // именнно тут происходит небольшая логика вывода, как вставить число 
                // подсчет пробелом исходя из числа (изначально 7 пробелов)
                string s = to_string(val);
                int pad   = 7 - (int)s.size();
                int left  = pad / 2;
                int right = pad - left;

                cout << color::get(val); 
                cout << string(left, ' ') << s << string(right, ' '); // пробелы + чило + пробелы
                cout << "\033[0m" << "|"; // сброс цвета 
            }
        }
        cout << "\n";
        cout << "+-------+-------+-------+-------+\n";
    }

    cout << "\n";
    cout << "controls: стрелки  |  exit: q\n";
}
