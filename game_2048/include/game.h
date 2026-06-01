#pragma once
#include "board.h"
#include "renderer.h"
#include "input.h"

class game {
private:
    board         b;   // поле
    renderer      r;   // вывод
    input_handler inp; // ввод

public:
    void run(); // главный цикл
};
