#include "pawn.h"
#include "square.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"

Pawn::Pawn(Board *b, PieceColor color, Square *pos, PieceType type)
: Piece{b, color, pos, type} {}

bool Pawn::isMoveValid(int row, int col) {
    int row = pos->getRow();
    int col = pos->getCol();
    std::vector <Square *> moves;
    if (color == PieceColor::Black) {
        if ((b->getCell(row + 1, col))->getPiece() == nullptr && inBound(row + 1, col)) {
            return true;
        } else if ((b->getCell(row + 1, col - 1))->getPiece() != nullptr && (b->getCell(row + 1, col - 1))->getPiece()->getColor() != color && inBound(row + 1, col - 1)) {
            return true;
        } else if ((b->getCell(row + 1, col + 1))->getPiece() != nullptr && (b->getCell(row + 1, col + 1))->getPiece()->getColor() != color && inBound(row + 1, col + 1)) {
            return true;
        } else if (row == 2 && (b->getCell(row + 2, col))->getPiece() == nullptr) {
            return true;
        }
    } else if (color == PieceColor::White) {
        if ((b->getCell(row - 1, col))->getPiece() == nullptr && inBound(row - 1, col)) {
            return true;
        } else if ((b->getCell(row - 1, col + 1))->getPiece() != nullptr && (b->getCell(row - 1, col + 1))->getPiece()->getColor() != color && inBound(row - 1, col + 1)) {
            return true;
        } else if ((b->getCell(row - 1, col - 1))->getPiece() != nullptr && (b->getCell(row - 1, col - 1))->getPiece()->getColor() != color && inBound(row + 1, col + 1)) {
            return true;
        } else if (row == 7 && (b->getCell(row - 2, col))->getPiece() == nullptr) {
            return true;
        }
    }
    return false;
}


void Pawn::calculateValidMoves() {
    validMoves.clear();
    int row = pos->getRow();
    int col = pos->getCol();
    std::vector <Square *> moves;
    if (color == PieceColor::Black) {
        if ((b->getCell(row + 1, col))->getPiece() == nullptr && inBound(row + 1, col)) {
            Square * m = b->getCell(row + 1, col);
            validMoves.emplace_back(m);
        }
        if ((b->getCell(row + 1, col - 1))->getPiece() != nullptr && (b->getCell(row + 1, col - 1))->getPiece()->getColor() != color && inBound(row + 1, col - 1)) {
            Square * m = b->getCell(row + 1, col - 1);
            validMoves.emplace_back(m);
        }
        if ((b->getCell(row + 1, col + 1))->getPiece() != nullptr && (b->getCell(row + 1, col + 1))->getPiece()->getColor() != color && inBound(row + 1, col + 1)) {
            Square * m = b->getCell(row + 1, col + 1);
            validMoves.emplace_back(m);
        }
        if (row == 2 && (b->getCell(row + 2, col))->getPiece() == nullptr) {
            Square * m = b->getCell(row + 2, col);
            validMoves.emplace_back(m);
        }
    } else if (color == PieceColor::White) {
        if ((b->getCell(row - 1, col))->getPiece() == nullptr && inBound(row - 1, col)) {
            Square * m = b->getCell(row - 1, col);
            validMoves.emplace_back(m);
        }
        if ((b->getCell(row - 1, col + 1))->getPiece() != nullptr && (b->getCell(row - 1, col + 1))->getPiece()->getColor() != color && inBound(row - 1, col + 1)) {
            Square * m = b->getCell(row - 1, col + 1);
            validMoves.emplace_back(m);
        }
        if ((b->getCell(row - 1, col - 1))->getPiece() != nullptr && (b->getCell(row - 1, col - 1))->getPiece()->getColor() != color && inBound(row - 1, col - 1)) {
            Square * m = b->getCell(row - 1, col - 1);
            validMoves.emplace_back(m);
        }
        if (row == 7 && (b->getCell(row - 2, col))->getPiece() == nullptr) {
            Square * m = b->getCell(row - 2, col);
            validMoves.emplace_back(m);
        }
    }
}

void Pawn::calculateCapturingMoves() {
    capturingMoves.clear();
    int row = pos->getRow();
    int col = pos->getCol();
    if (color == PieceColor::Black) {
        if ((b->getCell(row + 1, col - 1))->getPiece() != nullptr && (b->getCell(row + 1, col - 1))->getPiece()->getColor() != color && inBound(row + 1, col - 1)) {
            Square * m = b->getCell(row + 1, col - 1);
            capturingMoves.emplace_back(m);
        } 
        if ((b->getCell(row + 1, col + 1))->getPiece() != nullptr && (b->getCell(row + 1, col + 1))->getPiece()->getColor() != color && inBound(row + 1, col + 1)) {
            Square * m = b->getCell(row + 1, col + 1);
            capturingMoves.emplace_back(m);
        }
    } else if (color == PieceColor::White) {
        if ((b->getCell(row - 1, col + 1))->getPiece() != nullptr && (b->getCell(row - 1, col + 1))->getPiece()->getColor() != color && inBound(row - 1, col + 1)) {
            Square * m = b->getCell(row - 1, col + 1);
            capturingMoves.emplace_back(m);
        }
        if ((b->getCell(row - 1, col - 1))->getPiece() != nullptr && (b->getCell(row - 1, col - 1))->getPiece()->getColor() != color && inBound(row - 1, col - 1)) {
            Square * m = b->getCell(row - 1, col - 1);
            capturingMoves.emplace_back(m);
        }
    }
}

bool Pawn::canBeCaptured() {
    std::vector<Piece *> *list;
    if (color == PieceColor::Black) {
        list = b->getWhitePieces()->getPieces();
    } else if (color == PieceColor::White) {
        list =  b->getBlackPieces()->getPieces();
    }
    for (auto p: *list) {
        for (auto moves: p->getCapturingMoves()) {
            if (moves == pos) {
                return true;
            }
        }
    } return false;
}