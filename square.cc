#include "square.h"
#include "Pieces/piece.h"

Square::Square(int row, int col, Piece* piece) 
: row{row}, col{col}, piece{piece} {}

int Square::getRow() {
    return row;
}

int Square::getCol() {
    return col;
}

Piece* Square::getPiece() {
    return piece;
}

void Square::setPiece(Piece* newpiece) {
    piece = newpiece;
}

Square::~Square() {
    delete piece;
}