#include "color.h"

// по значению плитки возвращаем нужный ANSI цвет
string color::get(int val)
{
    switch (val)
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

// \033 - говорит терминалу дальше команда 