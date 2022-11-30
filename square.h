#ifndef __SQUARE_H__
#define __SQUARE_H__

class Piece;

class Square {
    const int row, col;
    Piece* piece;
public:
    Square(int row, int col, Piece* piece);
    int getRow();
    int getCol();
    Piece* getPiece();
    void setPiece(Piece* newpiece);
    ~Square();
};

#endif