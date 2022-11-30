#include "piece.h"
#include "piecelist.h"

Piece::Piece(Board *b, PieceColor color, Square *pos, PieceType type): b{b}, color{color}, pos{pos}, type{type} {}

PieceType Piece::getPieceType() {
    return type;
}

PieceColor Piece::getColor() {
    return color;
}

Square *Piece::getPosition() {
    return pos;
}