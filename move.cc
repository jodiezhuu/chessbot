#include "move.h"

Move::Move(Square* from, Square* to, Piece* piece) : from{from}, to{to}, piece{piece} {}

Square* Move::getFrom() {
    return from;
}

Square* Move::getTo() {
    return to;
}

Piece* Move::getPiece() {
    return piece;
}

void Move::setFrom(Square* newfrom) {
    from = newfrom;
}

void Move::setTo(Square* newto) {
    to = newto;
}

void Move::setPiece(Piece* newpiece) {
    piece = newpiece;
}
