#include "knight.h"

Knight::Knight(Board *b, PieceColor color, Square *pos, PieceType type)
: Piece{b, color, pos, type} {}

void Knight::calculateMoves() {
    validMoves.clear();
    capturingMoves.clear();
    // down left 
    if (inBound(pos->getRow() + 2, pos->getCol() - 1)) {
        if (b->getCell(pos->getRow() + 2, pos->getCol() - 1)->getPiece() == nullptr) {
            validMoves.push_back(b->getCell(pos->getRow() + 2, pos->getCol() - 1));
        } else if (b->getCell(pos->getRow() + 2, pos->getCol() - 1)->getPiece()->getColor() != color) {
            validMoves.push_back(b->getCell(pos->getRow() + 2, pos->getCol() - 1));
            capturingMoves.push_back(b->getCell(pos->getRow() + 2, pos->getCol() - 1));
        }
    }
    // down right
    if (inBound(pos->getRow() + 2, pos->getCol() + 1)) {
        if (b->getCell(pos->getRow() + 2, pos->getCol() + 1)->getPiece() == nullptr) {
            validMoves.push_back(b->getCell(pos->getRow() + 2, pos->getCol() + 1));
        } else if (b->getCell(pos->getRow() + 2, pos->getCol() + 1)->getPiece()->getColor() != color) {
            validMoves.push_back(b->getCell(pos->getRow() + 2, pos->getCol() + 1));
            capturingMoves.push_back(b->getCell(pos->getRow() + 2, pos->getCol() + 1));
        }
    }
    // right down
    if (inBound(pos->getRow() + 1, pos->getCol() + 2)) {
        if (b->getCell(pos->getRow() + 1, pos->getCol() + 2)->getPiece() == nullptr) {
            validMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() + 2));
        } else if (b->getCell(pos->getRow() + 1, pos->getCol() + 2)->getPiece()->getColor() != color) {
            validMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() + 2));
            capturingMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() + 2));
        } 
    }
    // right up
    if (inBound(pos->getRow() - 1, pos->getCol() + 2)) {
        if (b->getCell(pos->getRow() - 1, pos->getCol() + 2)->getPiece() == nullptr) {
            validMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() + 2));
        } else if (b->getCell(pos->getRow() - 1, pos->getCol() + 2)->getPiece()->getColor() != color) {
            validMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() + 2));
            capturingMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() + 2));
        }
    }
    // up left
    if (inBound(pos->getRow() - 2, pos->getCol() - 1)) {
        if (b->getCell(pos->getRow() - 2, pos->getCol() - 1)->getPiece() == nullptr) {
            validMoves.push_back(b->getCell(pos->getRow() - 2, pos->getCol() - 1));
        } else if (b->getCell(pos->getRow() - 2, pos->getCol() - 1)->getPiece()->getColor() != color) {
            validMoves.push_back(b->getCell(pos->getRow() - 2, pos->getCol() - 1));
            capturingMoves.push_back(b->getCell(pos->getRow() - 2, pos->getCol() - 1));
        }
    }
    // up right
    if (inBound(pos->getRow() - 2, pos->getCol() + 1)) {
        if (b->getCell(pos->getRow() - 2, pos->getCol() + 1)->getPiece() == nullptr) {
            validMoves.push_back(b->getCell(pos->getRow() - 2, pos->getCol() + 1));
        } else if (b->getCell(pos->getRow() - 2, pos->getCol() + 1)->getPiece()->getColor() != color) {
            validMoves.push_back(b->getCell(pos->getRow() - 2, pos->getCol() + 1));
            capturingMoves.push_back(b->getCell(pos->getRow() - 2, pos->getCol() + 1));
        }
    }
    // left down
    if (inBound(pos->getRow() + 1, pos->getCol() - 2)) {
        if (b->getCell(pos->getRow() + 1, pos->getCol() - 2)->getPiece() == nullptr) {
            validMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() - 2));
        } else if (b->getCell(pos->getRow() + 1, pos->getCol() - 2)->getPiece()->getColor() != color) {
            validMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() - 2));
            capturingMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() - 2));
        }
    }
    // left up
    if (inBound(pos->getRow() - 1, pos->getCol() - 2)) {
        if (b->getCell(pos->getRow() - 1, pos->getCol() - 2)->getPiece() == nullptr) {
            validMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() - 2));
        } else if (b->getCell(pos->getRow() - 1, pos->getCol() - 2)->getPiece()->getColor() != color) {
            validMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() - 2));
            capturingMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() - 2));
        }
    }
}