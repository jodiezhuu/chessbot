#include "piece.h"
#include "piecelist.h"

Piece::Piece(Board *b, PieceColor color, Square *pos, PieceType type): b{b}, color{color}, pos{pos}, type{type} {}

bool Piece::inBound(int row, int col) {
    return (0 <= row && row <= 7 && 0 <= col && col <= 7);
}

bool Piece::isMoveValid(int row, int col) {
    calculateMoves();
    for (auto moves : validMoves) {
        if (moves == b->getCell(row, col)) {
            return true;
        }
    }
    return false;
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

std::vector <Square *> Piece::getValidMoves() const{
    return validMoves;
}

std::vector <Square *> Piece::getCapturingMoves() const{
    return capturingMoves;
}


bool Piece::canBeCaptured() const {
    std::vector<Piece *> *list;
    if (color == PieceColor::White) {
        list = b->getBlackPieces()->getPieces();
    } else {
        list = b->getWhitePieces()->getPieces();
    }

    for (auto piece : *list) {
        for (auto moves : piece->getCapturingMoves()) {
            if (moves == pos) {
                return true;
            }
        }
    }
    return false;
}