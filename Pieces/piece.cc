#include "piece.h"
#include "piecelist.h"

Piece::Piece(Board *b, PieceColor color, Square *pos, PieceType type): b{b}, color{color}, pos{pos}, type{type} {}

bool Piece::inBound(int row, int col) {
    return (0 <= row && row <= 7 && 0 <= col && col <= 7);
}

PieceType Piece::getPieceType() const{
    return type;
}

PieceColor Piece::getColor() const{
    return color;
}

Square *Piece::getPosition() const{
    return pos;
}

std::vector <Square *> *Piece::getValidMoves() const{
    return &validMoves;
}

std::vector <Square *> *Piece::getCapturingMoves() const{
    return &capturingMoves;
}