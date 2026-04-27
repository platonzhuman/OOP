#include <iostream>

const int FIELD_WIDTH  = 7;
const int FIELD_HEIGHT = 6;
const int WIN_LENGTH   = 4;

// sost yacheek
enum Cell {
    EMPTY,
    RED,
    YELLOW
};

class Field {
public:
    Field(bool isRedFirst);          // constr
    void clear(bool isRedFirst);     // clear pole
    bool makeTurn(int column);       // go in column
    bool isWon(bool red) const;      // if red win
    bool isOver() const;             // if game over
    Cell getCell(int i, int j) const; // what is yachek
    bool isRedTurnNow() const;       // if who is go
    void print() const;              // show pole
    void printResult() const;        // vuvod result

private:
    Cell cells[FIELD_WIDTH][FIELD_HEIGHT];
    bool isRedTurn;
    Cell winner;

    void checkWinner();              // if win
};
