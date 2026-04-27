#include "four.h"
#include <iostream>

using namespace std;


// constr
Field::Field(bool isRedFirst) {
    clear(isRedFirst);
}

// clear pole
void Field::clear(bool isRedFirst) {
    isRedTurn = isRedFirst;
    winner = EMPTY;
    for (int i = 0; i < FIELD_WIDTH; ++i)
        for (int j = 0; j < FIELD_HEIGHT; ++j)
            cells[i][j] = EMPTY;
}

// go in column
bool Field::makeTurn(int column) {
    if (winner != EMPTY || column < 1 || column > FIELD_WIDTH)
        return false;

    int col = column - 1;
    for (int row = 0; row < FIELD_HEIGHT; ++row) {
        if (cells[col][row] == EMPTY) {
            cells[col][row] = isRedTurn ? RED : YELLOW;
            checkWinner();          // if win
            isRedTurn = !isRedTurn; // peredat over
            return true;
        }
    }
    return false; // column ready
}

// if win priveat
void Field::checkWinner() {
    const int DIR_NUMBER = 4;
    const int di[] = { 1, 0, 1, 1 };
    const int dj[] = { 0, 1, -1, 1 };

    for (int i = 0; i < FIELD_WIDTH; ++i) {
        for (int j = 0; j < FIELD_HEIGHT; ++j) {
            Cell start = cells[i][j];
            if (start == EMPTY) continue;

            for (int dir = 0; dir < DIR_NUMBER; ++dir) {
                int len = 1;
                int ni = i + di[dir];
                int nj = j + dj[dir];

                while (len < WIN_LENGTH) {
                    if (ni < 0 || ni >= FIELD_WIDTH || nj < 0 || nj >= FIELD_HEIGHT)
                        break;
                    if (cells[ni][nj] != start)
                        break;
                    ++len;
                    ni += di[dir];
                    nj += dj[dir];
                }
                if (len == WIN_LENGTH) {
                    winner = start;
                    return;
                }
            }
        }
    }
}

// if win red
bool Field::isWon(bool red) const {
    if (red) return winner == RED;
    else     return winner == YELLOW;
}

// if game over
bool Field::isOver() const {
    if (winner != EMPTY) return true;
    for (int i = 0; i < FIELD_WIDTH; ++i)
        for (int j = 0; j < FIELD_HEIGHT; ++j)
            if (cells[i][j] == EMPTY)
                return false;
    return true; // draw
}

// give soder yachek
Cell Field::getCell(int i, int j) const {
    return cells[i][j];
}

// who is go
bool Field::isRedTurnNow() const {
    return isRedTurn;
}

// show in terminal
void Field::print() const {
    cout << "\n   ";
    for (int i = 1; i <= FIELD_WIDTH; ++i) cout << i << "   ";
    cout << "\n";

    for (int j = FIELD_HEIGHT - 1; j >= 0; --j) {
        cout << j + 1 << " ";
        for (int i = 0; i < FIELD_WIDTH; ++i) {
            char ch = (cells[i][j] == RED) ? 'R' : (cells[i][j] == YELLOW ? 'Y' : ' ');
            cout << "| " << ch << " ";
        }
        cout << "|\n";
    }
    cout << "   ";
    for (int i = 0; i < FIELD_WIDTH; ++i) cout << "--- ";
    cout << "\n";
}


// show result game
void Field::printResult() const {
    if (winner == RED)
        cout << "win RED ^_^\n";
    else if (winner == YELLOW)
        cout << "win YELOW ^_^\n";
    else
        cout << "DRAW\n";
}