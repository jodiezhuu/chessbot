#include "pawn.h"
#include "../square.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"
#include <iostream>

Pawn::Pawn(Board *b, PieceColor color, Square *pos, PieceType type)
: Piece{b, color, pos, type} {
}

void Pawn::calculateAllMoves() {
    validMoves.clear();
    capturingMoves.clear();
    capturingMovesWithCheck.clear();
    movesToCapture.clear();
    if (b->getCell(pos->getRow(), pos->getCol())->getPiece() != this) return;
    if (color == PieceColor::Black) {
        // black moving down
        if (inBound(pos->getRow() + 1, pos->getCol()) && (b->getCell(pos->getRow() + 1, pos->getCol()))->getPiece() == nullptr) {
            validMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol()));
        }
        // black down left 
        if (inBound(pos->getRow() + 1, pos->getCol() - 1) && (b->getCell(pos->getRow() + 1, pos->getCol() - 1))->getPiece() != nullptr && (b->getCell(pos->getRow() + 1, pos->getCol() - 1))->getPiece()->getColor() != color) {
            validMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() - 1));
            capturingMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() - 1));
        } else if (inBound(pos->getRow() + 1, pos->getCol() - 1) && (b->getCell(pos->getRow() + 1, pos->getCol() - 1))->getPiece() == nullptr) {
            movesToCapture.push_back(b->getCell(pos->getRow() + 1, pos->getCol() - 1));
        }
        // black down right
        if (inBound(pos->getRow() + 1, pos->getCol() + 1) && (b->getCell(pos->getRow() + 1, pos->getCol() + 1))->getPiece() != nullptr && (b->getCell(pos->getRow() + 1, pos->getCol() + 1))->getPiece()->getColor() != color) {
            validMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() + 1));
            capturingMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() + 1));
        } else if (inBound(pos->getRow() + 1, pos->getCol() + 1) && (b->getCell(pos->getRow() + 1, pos->getCol() + 1))->getPiece() == nullptr) {
            movesToCapture.push_back(b->getCell(pos->getRow() + 1, pos->getCol() + 1));
        }
        // pawn in starting position, move two forward
        if (pos->getRow() == 1 && (b->getCell(pos->getRow() + 1, pos->getCol()))->getPiece() == nullptr && (b->getCell(pos->getRow() + 2, pos->getCol()))->getPiece() == nullptr) {
            validMoves.push_back(b->getCell(pos->getRow() + 2, pos->getCol()));
        }
        // en passant
        if (inBound(pos->getRow() + 1, pos->getCol() + 1) && inBound(pos->getRow(), pos->getCol() + 1) && b->getCell(pos->getRow() + 1, pos->getCol() + 1)->getPiece() == nullptr && b->getCell(pos->getRow(), pos->getCol() + 1)->getPiece() != nullptr && b->getCell(pos->getRow(), pos->getCol() + 1)->getPiece()->getPieceType() == PieceType::WhitePawn && b->getCell(pos->getRow(), pos->getCol() + 1)->getPiece()->getHasPawnMovedTwo() == true) {
            validMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() + 1));
            capturingMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() + 1));
            b->getCell(pos->getRow(), pos->getCol() + 1)->getPiece()->setHasEnPassant(true);
        }
        // en passant
        if (inBound(pos->getRow() + 1, pos->getCol() - 1) && inBound(pos->getRow(), pos->getCol() - 1) && b->getCell(pos->getRow() + 1, pos->getCol() - 1)->getPiece() == nullptr && b->getCell(pos->getRow(), pos->getCol() - 1)->getPiece() != nullptr && b->getCell(pos->getRow(), pos->getCol() - 1)->getPiece()->getPieceType() == PieceType::WhitePawn && b->getCell(pos->getRow(), pos->getCol() - 1)->getPiece()->getHasPawnMovedTwo() == true) {
            validMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() - 1));
            capturingMoves.push_back(b->getCell(pos->getRow() + 1, pos->getCol() - 1));  
            b->getCell(pos->getRow(), pos->getCol() - 1)->getPiece()->setHasEnPassant(true);     
        }
    } else if (color == PieceColor::White) {
        // white move up
        if (inBound(pos->getRow() - 1, pos->getCol()) && (b->getCell(pos->getRow() - 1, pos->getCol()))->getPiece() == nullptr) {
            validMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol()));
        }
        // white up right
        if (inBound(pos->getRow() - 1, pos->getCol() + 1) && (b->getCell(pos->getRow() - 1, pos->getCol() + 1))->getPiece() != nullptr && (b->getCell(pos->getRow() - 1, pos->getCol() + 1))->getPiece()->getColor() != color) {
            validMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() + 1));
            capturingMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() + 1));
        } else if (inBound(pos->getRow() - 1, pos->getCol() + 1) && (b->getCell(pos->getRow() - 1, pos->getCol() + 1))->getPiece() == nullptr) {
            movesToCapture.push_back(b->getCell(pos->getRow() - 1, pos->getCol() + 1));
        }
        // white up left
        if (inBound(pos->getRow() - 1, pos->getCol() - 1) && (b->getCell(pos->getRow() - 1, pos->getCol() - 1))->getPiece() != nullptr && (b->getCell(pos->getRow() - 1, pos->getCol() - 1))->getPiece()->getColor() != color) {
            validMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() - 1));
            capturingMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() - 1));
        } else if (inBound(pos->getRow() - 1, pos->getCol() - 1) && (b->getCell(pos->getRow() - 1, pos->getCol() - 1))->getPiece() == nullptr) {
            movesToCapture.push_back(b->getCell(pos->getRow() - 1, pos->getCol() - 1));
        }
        // white in starting position, up two 
        if (pos->getRow() == 6 && (b->getCell(pos->getRow() - 1, pos->getCol()))->getPiece() == nullptr && (b->getCell(pos->getRow() - 2, pos->getCol()))->getPiece() == nullptr) {
            validMoves.push_back(b->getCell(pos->getRow() - 2, pos->getCol()));
        }
        // en passant
        if (inBound(pos->getRow() - 1, pos->getCol() + 1) && inBound(pos->getRow(), pos->getCol() + 1) && b->getCell(pos->getRow() - 1, pos->getCol() + 1)->getPiece() == nullptr && b->getCell(pos->getRow(), pos->getCol() + 1)->getPiece() != nullptr && b->getCell(pos->getRow(), pos->getCol() + 1)->getPiece()->getPieceType() == PieceType::BlackPawn && b->getCell(pos->getRow(), pos->getCol() + 1)->getPiece()->getHasPawnMovedTwo() == true) {
            validMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() + 1));
            capturingMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() + 1));
            b->getCell(pos->getRow(), pos->getCol() + 1)->getPiece()->setHasEnPassant(true);
        }
        // en passant
        if (inBound(pos->getRow() - 1, pos->getCol() - 1) && inBound(pos->getRow(), pos->getCol() - 1) && b->getCell(pos->getRow() - 1, pos->getCol() - 1)->getPiece() == nullptr && b->getCell(pos->getRow(), pos->getCol() - 1)->getPiece() != nullptr && b->getCell(pos->getRow(), pos->getCol() - 1)->getPiece()->getPieceType() == PieceType::BlackPawn && b->getCell(pos->getRow(), pos->getCol() - 1)->getPiece()->getHasPawnMovedTwo() == true) {
            validMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() - 1));
            capturingMoves.push_back(b->getCell(pos->getRow() - 1, pos->getCol() - 1));     
            b->getCell(pos->getRow(), pos->getCol() - 1)->getPiece()->setHasEnPassant(true);    
        }
    }
}
