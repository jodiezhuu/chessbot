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
            if (piece->getColor() == color) break;
            if (piece == nullptr) {
                validMoves.push_back(sq);
            } else if (piece->getColor() != color) {
                validMoves.push_back(sq);
                capturingMoves.push_back(sq);
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
            if (piece->getColor() == color) break;
            if (piece == nullptr) {
                validMoves.push_back(sq);
            } else if (piece->getColor() != color) {
                validMoves.push_back(sq);
                capturingMoves.push_back(sq);
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
            if (piece->getColor() == color) break;
            if (piece == nullptr) {
                validMoves.push_back(sq);
            } else if (piece->getColor() != color) {
                validMoves.push_back(sq);
                capturingMoves.push_back(sq);
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
            if (piece->getColor() == color) break;
            if (piece == nullptr) {
                validMoves.push_back(sq);
            } else if (piece->getColor() != color) {
                validMoves.push_back(sq);
                capturingMoves.push_back(sq);
                break;
            }
        }
    }
}