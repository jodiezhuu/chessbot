#include "square.h"

Square::Square(int row, int col) 
: row{row}, col{col} {}

int Square::getRow() {
    return row;
}

int Square::getCol() {
    return col;
}