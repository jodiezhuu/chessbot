#include "pawn.h"
#include "../square.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"

Pawn::Pawn(Board *b, PieceColor color, Square *pos, PieceType type)
: Piece{b, color, pos, type} {}

bool Pawn::isMoveValid(int row, int col) {
    std::vector <Square *> moves;
    if (color == PieceColor::Black) {
        if ((b->getCell(pos->getRow() + 1, pos->getCol()))->getPiece() == nullptr && inBound(pos->getRow() + 1, pos->getCol())) {
            return true;
        } else if ((b->getCell(pos->getRow() + 1, pos->getCol() - 1))->getPiece() != nullptr && (b->getCell(pos->getRow() + 1, pos->getCol() - 1))->getPiece()->getColor() != color && inBound(pos->getRow() + 1, pos->getCol() - 1)) {
            return true;
        } else if ((b->getCell(pos->getRow() + 1, pos->getCol() + 1))->getPiece() != nullptr && (b->getCell(pos->getRow() + 1, pos->getCol() + 1))->getPiece()->getColor() != color && inBound(pos->getRow() + 1, pos->getCol() + 1)) {
            return true;
        } else if (pos->getRow() == 2 && (b->getCell(pos->getRow() + 2, pos->getCol()))->getPiece() == nullptr) {
            return true;
        }
    } else if (color == PieceColor::White) {
        if ((b->getCell(pos->getRow() - 1, pos->getCol()))->getPiece() == nullptr && inBound(pos->getRow() - 1, pos->getCol())) {
            return true;
        } else if ((b->getCell(pos->getRow() - 1, pos->getCol() + 1))->getPiece() != nullptr && (b->getCell(pos->getRow() - 1, pos->getCol() + 1))->getPiece()->getColor() != color && inBound(pos->getRow() - 1, pos->getCol() + 1)) {
            return true;
        } else if ((b->getCell(pos->getRow() - 1, pos->getCol() - 1))->getPiece() != nullptr && (b->getCell(pos->getRow() - 1, pos->getCol() - 1))->getPiece()->getColor() != color && inBound(pos->getRow() + 1, pos->getCol() + 1)) {
            return true;
        } else if (pos->getRow() == 7 && (b->getCell(pos->getRow() - 2, pos->getCol()))->getPiece() == nullptr) {
            return true;
        }
    }
    return false;
}


void Pawn::calculateValidMoves() {
    validMoves.clear();
    std::vector <Square *> moves;
    if (color == PieceColor::Black) {
        if ((b->getCell(pos->getRow() + 1, pos->getCol()))->getPiece() == nullptr && inBound(pos->getRow() + 1, pos->getCol())) {
            Square * m = b->getCell(pos->getRow() + 1, pos->getCol());
            validMoves.emplace_back(m);
        }
        if ((b->getCell(pos->getRow() + 1, pos->getCol() - 1))->getPiece() != nullptr && (b->getCell(pos->getRow() + 1, pos->getCol() - 1))->getPiece()->getColor() != color && inBound(pos->getRow() + 1, pos->getCol() - 1)) {
            Square * m = b->getCell(pos->getRow() + 1, pos->getCol() - 1);
            validMoves.emplace_back(m);
        }
        if ((b->getCell(pos->getRow() + 1, pos->getCol() + 1))->getPiece() != nullptr && (b->getCell(pos->getRow() + 1, pos->getCol() + 1))->getPiece()->getColor() != color && inBound(pos->getRow() + 1, pos->getCol() + 1)) {
            Square * m = b->getCell(pos->getRow() + 1, pos->getCol() + 1);
            validMoves.emplace_back(m);
        }
        if (pos->getRow() == 2 && (b->getCell(pos->getRow() + 2, pos->getCol()))->getPiece() == nullptr) {
            Square * m = b->getCell(pos->getRow() + 2, pos->getCol());
            validMoves.emplace_back(m);
        }
    } else if (color == PieceColor::White) {
        if ((b->getCell(pos->getRow() - 1, pos->getCol()))->getPiece() == nullptr && inBound(pos->getRow() - 1, pos->getCol())) {
            Square * m = b->getCell(pos->getRow() - 1, pos->getCol());
            validMoves.emplace_back(m);
        }
        if ((b->getCell(pos->getRow() - 1, pos->getCol() + 1))->getPiece() != nullptr && (b->getCell(pos->getRow() - 1, pos->getCol() + 1))->getPiece()->getColor() != color && inBound(pos->getRow() - 1, pos->getCol() + 1)) {
            Square * m = b->getCell(pos->getRow() - 1, pos->getCol() + 1);
            validMoves.emplace_back(m);
        }
        if ((b->getCell(pos->getRow() - 1, pos->getCol() - 1))->getPiece() != nullptr && (b->getCell(pos->getRow() - 1, pos->getCol() - 1))->getPiece()->getColor() != color && inBound(pos->getRow() - 1, pos->getCol() - 1)) {
            Square * m = b->getCell(pos->getRow() - 1, pos->getCol() - 1);
            validMoves.emplace_back(m);
        }
        if (pos->getRow() == 7 && (b->getCell(pos->getRow() - 2, pos->getCol()))->getPiece() == nullptr) {
            Square * m = b->getCell(pos->getRow() - 2, pos->getCol());
            validMoves.emplace_back(m);
        }
    }
}

void Pawn::calculateCapturingMoves() {
    capturingMoves.clear();
    if (color == PieceColor::Black) {
        if ((b->getCell(pos->getRow() + 1, pos->getCol() - 1))->getPiece() != nullptr && (b->getCell(pos->getRow() + 1, pos->getCol() - 1))->getPiece()->getColor() != color && inBound(pos->getRow() + 1, pos->getCol() - 1)) {
            Square * m = b->getCell(pos->getRow() + 1, pos->getCol() - 1);
            capturingMoves.emplace_back(m);
        } 
        if ((b->getCell(pos->getRow() + 1, pos->getCol() + 1))->getPiece() != nullptr && (b->getCell(pos->getRow() + 1, pos->getCol() + 1))->getPiece()->getColor() != color && inBound(pos->getRow() + 1, pos->getCol() + 1)) {
            Square * m = b->getCell(pos->getRow() + 1, pos->getCol() + 1);
            capturingMoves.emplace_back(m);
        }
    } else if (color == PieceColor::White) {
        if ((b->getCell(pos->getRow() - 1, pos->getCol() + 1))->getPiece() != nullptr && (b->getCell(pos->getRow() - 1, pos->getCol() + 1))->getPiece()->getColor() != color && inBound(pos->getRow() - 1, pos->getCol() + 1)) {
            Square * m = b->getCell(pos->getRow() - 1, pos->getCol() + 1);
            capturingMoves.emplace_back(m);
        }
        if ((b->getCell(pos->getRow() - 1, pos->getCol() - 1))->getPiece() != nullptr && (b->getCell(pos->getRow() - 1, pos->getCol() - 1))->getPiece()->getColor() != color && inBound(pos->getRow() - 1, pos->getCol() - 1)) {
            Square * m = b->getCell(pos->getRow() - 1, pos->getCol() - 1);
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