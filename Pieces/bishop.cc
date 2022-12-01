#include "bishop.h"

Bishop::Bishop(Board *b, PieceColor color, Square *pos, PieceType type)
: Piece{b, color, pos, type} {}

void Bishop::calculateMoves() {
    // left-up diagonal
    for (int row = pos->getRow() - 1; row >= 0; --row) {
        for (int col = pos->getCol() - 1; col >= 0; --col) {
            if (!inBound(row, col)) break;
            Square * sq = b->getCell(row, col);
            Piece *piece = sq->getPiece();
            if (piece == nullptr) {
                validMoves.emplace_back(sq);
            } else if (piece->getColor() != color) {
                validMoves.emplace_back(sq);
                capturingMoves.emplace_back(sq);
                break;
            }
        }
    }
    // right-up diagonal
    for (int row = pos->getRow() - 1; row >= 0; --row) {
        for (int col = pos->getCol() + 1; col <= 7; ++col) {
            if (!inBound(row, col)) break;
            Square * sq = b->getCell(row, col);
            Piece *piece = sq->getPiece();
            if (piece == nullptr) {
                validMoves.emplace_back(sq);
            } else if (piece->getColor() != color) {
                validMoves.emplace_back(sq);
                capturingMoves.emplace_back(sq);
                break;
            }
        }
    }
    // left-down diagonal
    for (int row = pos->getRow() + 1; row <= 7; ++row) {
        for (int col = pos->getCol() - 1; col >= 0; --col) {
            if (!inBound(row, col)) break;
            Square * sq = b->getCell(row, col);
            Piece *piece = sq->getPiece();
            if (piece == nullptr) {
                validMoves.emplace_back(sq);
            } else if (piece->getColor() != color) {
                validMoves.emplace_back(sq);
                capturingMoves.emplace_back(sq);
                break;
            }
        }
    }
    // right-down diagonal
    for (int row = pos->getRow() + 1; row <= 7; ++row) {
        for (int col = pos->getCol() + 1; col <= 7; ++col) {
            if (!inBound(row, col)) break;
            Square * sq = b->getCell(row, col);
            Piece *piece = sq->getPiece();
            if (piece == nullptr) {
                validMoves.emplace_back(sq);
            } else if (piece->getColor() != color) {
                validMoves.emplace_back(sq);
                capturingMoves.emplace_back(sq);
                break;
            }
        }
    }
}