#include "bishop.h"
#include <iostream>

Bishop::Bishop(Board *b, PieceColor color, Square *pos, PieceType type)
: Piece{b, color, pos, type} {
}

void Bishop::calculateAllMoves() {
    validMoves.clear();
    capturingMoves.clear();
    capturingMovesWithCheck.clear();
    if (b->getCell(pos->getRow(), pos->getCol())->getPiece() != this) return;
    // left-up diagonal
    for (int i = 1; i <= 7; ++i) {
        if (!inBound(pos->getRow() - i, pos->getCol() - i)) break;
        Square * sq = b->getCell(pos->getRow() - i, pos->getCol() - i);
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

    // right-up diagonal
    for (int i = 1; i <= 7; ++i) {
        if (!inBound(pos->getRow() - i, pos->getCol() + i)) break;
        Square * sq = b->getCell(pos->getRow() - i, pos->getCol() + i);
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
    // left-down diagonal
    for (int i = 1; i <= 7; ++i) {
        if (!inBound(pos->getRow() + i, pos->getCol() - i)) break;
        Square * sq = b->getCell(pos->getRow() + i, pos->getCol() - i);
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
    // right-down diagonal
    for (int i = 1; i <= 7; ++i) {
        if (!inBound(pos->getRow() + i, pos->getCol() + i)) break;
        Square * sq = b->getCell(pos->getRow() + i, pos->getCol() + i);
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