#include "piece.h"
#include "piecelist.h"
#include <iostream>

Piece::Piece(Board *b, PieceColor color, Square *pos, PieceType type, bool hasMoved): b{b}, color{color}, pos{pos}, type{type}, hasMoved{hasMoved} {}

Piece::~Piece() {}

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

    // if ((int) color == 0) {
    //     std::cout << "White Capturing Moves: " << std::endl;
    // } else {
    //     std::cout << "Black Capturing Moves: " << std::endl;
    // }
    for (auto piece : *list) {
        // std::cout << "[" << piece->getPosition()->getRow() << "," << piece->getPosition()->getCol() << "]: " << (int) piece->getPieceType() << ": ";
        for (auto moves : piece->getCapturingMoves()) {
            // std::cout << "(" << moves->getRow() << "," << moves->getCol() << ") ";
            if (moves == pos) {
                return true;
            }
        }
        // std::cout << std::endl;
    }
    return false;
}

bool Piece::getHasMoved() const {
    return hasMoved;
}

void Piece::setPosition(int newrow, int newcol) {
    pos = b->getCell(newrow, newcol);
}

void Piece::setHasMoved(bool val) {
    hasMoved = val;
}