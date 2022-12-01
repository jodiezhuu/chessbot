#include "queen.h"

Queen::Queen(Board *b, PieceColor color, Square *pos, PieceType type)
: Piece{b, color, pos, type} {}

void Queen::calculateMoves() {
    validMoves.clear();
    capturingMoves.clear();
    // right
    for (int col = pos->getCol() + 1; col <= 7; ++col) {
        if (!inBound(pos->getRow(), col)) break;
        Square * sq = b->getCell(pos->getRow(), col);
        Piece *piece = sq->getPiece();
        if (piece == nullptr) {
            validMoves.emplace_back(sq);
        } else if (piece->getColor() != color) {
            validMoves.emplace_back(sq);
            capturingMoves.emplace_back(sq);
            break;
        }
    }
    // left
    for (int col = pos->getCol() - 1; col >= 0; --col) {
        if (!inBound(pos->getRow(), col)) break;
        Square * sq = b->getCell(pos->getRow(), col);
        Piece *piece = sq->getPiece();
        if (piece == nullptr) {
            validMoves.emplace_back(sq);
        } else if (piece->getColor() != color) {
            validMoves.emplace_back(sq);
            capturingMoves.emplace_back(sq);
            break;
        }
    }
    // up
    for (int row = pos->getRow() - 1; row >= 0; --row) {
        if (!inBound(row, pos->getCol())) break;
        Square * sq = b->getCell(row, pos->getCol());
        Piece *piece = sq->getPiece();
        if (piece == nullptr) {
            validMoves.emplace_back(sq);
        } else if (piece->getColor() != color) {
            validMoves.emplace_back(sq);
            capturingMoves.emplace_back(sq);
            break;
        }
    }
    // down
    for (int row = pos->getRow() + 1; row <= 7; ++row) {
        if (!inBound(row, pos->getCol())) break;
        Square * sq = b->getCell(row, pos->getCol());
        Piece *piece = sq->getPiece();
        if (piece == nullptr) {
            validMoves.emplace_back(sq);
        } else if (piece->getColor() != color) {
            validMoves.emplace_back(sq);
            capturingMoves.emplace_back(sq);
            break;
        }
    }
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

bool Queen::canBeCaptured() {
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