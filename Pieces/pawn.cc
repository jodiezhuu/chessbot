#include "pawn.h"
#include "../square.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"

Pawn::Pawn(Board *b, PieceColor color, Square *pos, PieceType type)
: Piece{b, color, pos, type} {}

void Pawn::calculateMoves() {
    validMoves.clear();
    capturingMoves.clear();
    if (color == PieceColor::Black) {
        if ((b->getCell(pos->getRow() + 1, pos->getCol()))->getPiece() == nullptr && inBound(pos->getRow() + 1, pos->getCol())) {
            validMoves.emplace_back(pos->getRow() + 1, pos->getCol());
        }
        if ((b->getCell(pos->getRow() + 1, pos->getCol() - 1))->getPiece() != nullptr && (b->getCell(pos->getRow() + 1, pos->getCol() - 1))->getPiece()->getColor() != color && inBound(pos->getRow() + 1, pos->getCol() - 1)) {
            validMoves.emplace_back(b->getCell(pos->getRow() + 1, pos->getCol() - 1));
            capturingMoves.emplace_back(b->getCell(pos->getRow() + 1, pos->getCol() - 1));
        } 
        if ((b->getCell(pos->getRow() + 1, pos->getCol() + 1))->getPiece() != nullptr && (b->getCell(pos->getRow() + 1, pos->getCol() + 1))->getPiece()->getColor() != color && inBound(pos->getRow() + 1, pos->getCol() + 1)) {
            validMoves.emplace_back(b->getCell(pos->getRow() + 1, pos->getCol() + 1));
            capturingMoves.emplace_back(b->getCell(pos->getRow() + 1, pos->getCol() + 1));
        }
        if (pos->getRow() == 2 && (b->getCell(pos->getRow() + 2, pos->getCol()))->getPiece() == nullptr) {
            Square * m = b->getCell(pos->getRow() + 2, pos->getCol());
            validMoves.emplace_back(m);
        }
    } else if (color == PieceColor::White) {
        if ((b->getCell(pos->getRow() - 1, pos->getCol()))->getPiece() == nullptr && inBound(pos->getRow() - 1, pos->getCol())) {
            validMoves.emplace_back(b->getCell(pos->getRow() - 1, pos->getCol()));
        }
        if ((b->getCell(pos->getRow() - 1, pos->getCol() + 1))->getPiece() != nullptr && (b->getCell(pos->getRow() - 1, pos->getCol() + 1))->getPiece()->getColor() != color && inBound(pos->getRow() - 1, pos->getCol() + 1)) {
            validMoves.emplace_back(pos->getRow() - 1, pos->getCol() + 1);
            capturingMoves.emplace_back(pos->getRow() - 1, pos->getCol() + 1);
        }
        if ((b->getCell(pos->getRow() - 1, pos->getCol() - 1))->getPiece() != nullptr && (b->getCell(pos->getRow() - 1, pos->getCol() - 1))->getPiece()->getColor() != color && inBound(pos->getRow() - 1, pos->getCol() - 1)) {
            validMoves.emplace_back(pos->getRow() - 1, pos->getCol() - 1);
            capturingMoves.emplace_back(pos->getRow() - 1, pos->getCol() - 1);
        }
        if (pos->getRow() == 7 && (b->getCell(pos->getRow() - 2, pos->getCol()))->getPiece() == nullptr) {
            validMoves.emplace_back(pos->getRow() - 2, pos->getCol());
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