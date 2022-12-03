#include "queen.h"

Queen::Queen(Board *b, PieceColor color, Square *pos, PieceType type)
: Piece{b, color, pos, type} {
}

void Queen::calculateMoves() {
    validMoves.clear();
    capturingMoves.clear();
    if (b->getCell(pos->getRow(), pos->getCol())->getPiece() != this) return;
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
