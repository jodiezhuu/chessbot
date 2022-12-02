#include "rook.h"
#include <iostream>

Rook::Rook(Board *b, PieceColor color, Square *pos, PieceType type)
: Piece{b, color, pos, type} {}

void Rook::calculateMoves() {
    validMoves.clear();
    capturingMoves.clear();
    // right
    for (int col = pos->getCol() + 1; col <= 7; ++col) {
        if (!inBound(pos->getRow(), col)) break;
        Square * sq = b->getCell(pos->getRow(), col);
        Piece *piece = sq->getPiece();
        if (piece == nullptr) {
            validMoves.push_back(sq);
        } else if (piece->getColor() == color) {
            break;
        } else if (piece->getColor() != color) {
            validMoves.push_back(sq);
            capturingMoves.push_back(sq);
            break;
        }
    }
    // left
    for (int col = pos->getCol() - 1; col >= 0; --col) {
        if (!inBound(pos->getRow(), col)) break;
        Square * sq = b->getCell(pos->getRow(), col);
        Piece *piece = sq->getPiece();
        if (piece == nullptr) {
            validMoves.push_back(sq);
        } else if (piece->getColor() == color) {
            break;
        } else if (piece->getColor() != color) {
            validMoves.push_back(sq);
            capturingMoves.push_back(sq);
            break;
        }
    }
        // up
    for (int row = pos->getRow() - 1; row >= 0; --row) {
        if (!inBound(row, pos->getCol())) break;
        Square * sq = b->getCell(row, pos->getCol());
        Piece *piece = sq->getPiece();
        if (piece == nullptr) {
            validMoves.push_back(sq);
        } else if (piece->getColor() == color) {
            break;
        } else if (piece->getColor() != color) {
            validMoves.push_back(sq);
            capturingMoves.push_back(sq);
            break;
        }
    }
    // down
    for (int row = pos->getRow() + 1; row <= 7; ++row) {
        if (!inBound(row, pos->getCol())) break;
        Square * sq = b->getCell(row, pos->getCol());
        Piece *piece = sq->getPiece();
        if (piece == nullptr) {
            validMoves.push_back(sq);
        } else if (piece->getColor() == color) {
            break;
        } else if (piece->getColor() != color) {
            validMoves.push_back(sq);
            capturingMoves.push_back(sq);
            break;
        }
    }
}