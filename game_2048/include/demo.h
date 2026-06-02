#pragma once
#include "board.h"
#include "renderer.h"

class demo {
private:
    board    b;
    renderer r;

    char get_move(); // подобрать действенный ход перебором направлений

public:
    void run(); // демо цикл — комп играет сам
};
