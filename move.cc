#include "move.h"

// move constructor
Move::Move(Square* from, Square* to, Piece* piece) : from{from}, to{to}, piece{piece} {}

// accessor for Square* from
Square* Move::getFrom() {
    return from;
}

// accessor for Square* to
Square* Move::getTo() {
    return to;
}

// accessor for Piece* piece
Piece* Move::getPiece() {
    return piece;
}

// mutator for Square* from
void Move::setFrom(Square* newfrom) {
    from = newfrom;
}

// mutator for Square* to
void Move::setTo(Square* newto) {
    to = newto;
}

// mutator for Piece* piece
void Move::setPiece(Piece* newpiece) {
    piece = newpiece;
}
