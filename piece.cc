#include "piece.h"
#include "piecelist.h"
#include "square.h"

PieceType Piece::getPieceType() {
    return type;
}

PieceColor Piece::getColor() {
    return color;
}

Square *Piece::getPosition() {
    return pos;
}