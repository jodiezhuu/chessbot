#include "piece.h"
#include "piecelist.h"
#include "square.h"

Piece::Piece(PieceColor color, Square *pos, PieceType type): color{color}, pos{pos}, type{type} {}

PieceType Piece::getPieceType() {
    return type;
}

PieceColor Piece::getColor() {
    return color;
}

Square *Piece::getPosition() {
    return pos;
}