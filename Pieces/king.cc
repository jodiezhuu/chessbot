#include "king.h"
#include "../square.h"

King::King(Board *b, PieceColor color, Square *pos, PieceType type) 
: Piece{b, color, pos, type} {}

bool King::moveInCheck(int row, int col) {
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

void King::calculateMoves() {
    validMoves.clear();
    capturingMoves.clear();
    for (int row = pos->getRow() - 1; row <= pos->getRow() + 1; ++row) {
        for (int col = pos->getCol() - 1; col <= pos->getCol() + 1; ++col) {
            if (!(inBound(row, col) && (row != pos->getRow() && col != pos->getCol()))) continue;
            Piece * piece = b->getCell(row, col)->getPiece();
            if (piece == nullptr && !moveInCheck(row, col)) {
                validMoves.emplace_back(b->getCell(row, col));
            } else if (piece != nullptr && piece->getColor() != color && !moveInCheck(row, col)) {
                validMoves.emplace_back(b->getCell(row, col));
                capturingMoves.emplace_back(b->getCell(row, col));
            }
        }
    }
}

bool King::canBeCaptured() {
    return moveInCheck(pos->getRow(), pos->getCol());
}