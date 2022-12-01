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
            if (!inBound(row, col) || (row == pos->getRow() && col == pos->getCol())) continue;
            Piece * piece = b->getCell(row, col)->getPiece();
            if (piece == nullptr) {
                validMoves.push_back(b->getCell(row, col));
            } else if (piece != nullptr) {
                if (piece->getColor() == color) {
                    continue;
                } else {
                    validMoves.push_back(b->getCell(row, col));
                    capturingMoves.push_back(b->getCell(row, col));
                }                
            }
        }
    } 
}

void King::filterChecks() {
    for (auto m = validMoves.begin(); m != validMoves.end(); ++m) {
        if (moveInCheck((*m)->getRow(), (*m)->getCol())) {
            validMoves.erase(m);
        }
    }
    for (auto cm = capturingMoves.begin(); cm != capturingMoves.end(); ++cm) {
        if (moveInCheck((*cm)->getRow(), (*cm)->getCol())) {
            capturingMoves.erase(cm);
        }
    }
}