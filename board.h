#pragma once

#include <cstdlib>
#include <ctime>
#include<iostream>
#include<conio.h>

using namespace std;


enum squarestate{
    hidden=0,
    unhidden=1,
    flagged=2,
    marked=3
};
enum squaretype{
    empty=0,
    one=1, two=2, three=3, four=4, five=5, six=6, seven=7, eight=8,
    bomb=9
};
struct square{
    squarestate state;
    squaretype type;
    squarestate oldstate;
};

class Board{
public:
    ///Board();
    ~Board();
    Board(unsigned int columns, unsigned int rows, unsigned int bombs);

    void PrintBoard();
    void PrintNumbersBoard();

    void DiscoverSquare(const unsigned int x, const unsigned int y);
    void SetFlag(const unsigned int x, const unsigned int y);
    void SetMark(const unsigned int x, const unsigned int y);
    void SetMarkButton(const unsigned int x);

    unsigned int GetCX();
    unsigned int GetCY();
    void UpdateCursor(const char a);

    bool IsNotOver();
    bool CheckForWin();

private:

    unsigned int number_of_rows;
    unsigned int number_of_columns;
    unsigned int number_of_bombs;
    unsigned int GetNumberOfBombs();
    unsigned int cx;
    unsigned int cy;
    unsigned int mark_button;
    unsigned int square_counter;
    unsigned int flagged_counter;
    bool existence;
    square *board;

    void ShowBomb(const unsigned int x, const unsigned int y);
    void HideBomb(const unsigned int x, const unsigned int y);
};

