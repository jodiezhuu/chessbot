#include "square.h"
#include "Pieces/piece.h"

// Square constructor
Square::Square(int row, int col, Piece* piece) 
: row{row}, col{col}, piece{piece} {}

// accessor for row
int Square::getRow() {
    return row;
}

// accessor for column
int Square::getCol() {
    return col;
}

// accesor for piece
Piece* Square::getPiece() {
    return piece;
}

// mutator for piece
void Square::setPiece(Piece* newpiece) {
    piece = newpiece;
}

// Square destructor
Square::~Square() {
    delete piece;
}