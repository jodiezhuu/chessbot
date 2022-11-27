#ifndef __SQUARE_H__
#define __SQUARE_H__

class Square {
    const int row, col;
public:
    Square(int row, int col);
    int getRow();
    int getCol();
};

#endif