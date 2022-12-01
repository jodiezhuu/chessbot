#include "piece.h"
#include "piecelist.h"
#include <iostream>

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

std::vector <Square *> Piece::getValidMoves() {
    calculateMoves();
    return validMoves;
}

std::vector <Square *> Piece::getCapturingMoves() {
    calculateMoves();
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
        std::cout << "[" << piece->getPosition()->getRow() << "," << piece->getPosition()->getCol() << "]: " << (int) piece->getPieceType() << ": ";
        for (auto moves : piece->getCapturingMoves()) {
            std::cout << "(" << moves->getRow() << "," << moves->getCol() << ") ";
            if (moves == pos) {
                return true;
            }
        }
        std::cout << std::endl;
    }
    return false;
}