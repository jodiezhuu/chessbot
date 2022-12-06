#include "king.h"
#include "../square.h"
#include "rook.h"
#include <vector>
#include <iostream>

King::King(Board *b, PieceColor color, Square *pos, PieceType type) 
: Piece{b, color, pos, type} {}

// Can move one square in any direction
void King::calculateAllMoves() {
    validMoves.clear();
    capturingMoves.clear();
    capturingMovesWithCheck.clear();
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

    //Check for castling possibility
    if (!hasMoved) {
        if (color == PieceColor::Black) {
            //Checks both rooks
            Piece* rook1 = b->getCell(0, 0)->getPiece();
            if (rook1 != nullptr && rook1->getPieceType() == PieceType::BlackRook && !(rook1->getHasMoved())) {
                if (b->getCell(0, 1)->getPiece() == nullptr && b->getCell(0, 2)->getPiece() == nullptr && b->getCell(0, 3)->getPiece() == nullptr) {
                    validMoves.push_back(b->getCell(0, 2));
                }
            }
            Piece* rook2 = b->getCell(0, 7)->getPiece();
            if (rook2 != nullptr && rook2->getPieceType() == PieceType::BlackRook && !(rook2->getHasMoved())) {
                if (b->getCell(0, 6)->getPiece() == nullptr && b->getCell(0, 5)->getPiece() == nullptr) {
                    validMoves.push_back(b->getCell(0, 6));
                }
            }
        } else {
            //Checks both rooks
            Piece* rook1 = b->getCell(7, 0)->getPiece();
            if (rook1 != nullptr && rook1->getPieceType() == PieceType::WhiteRook && !(rook1->getHasMoved())) {
                if (b->getCell(7, 1)->getPiece() == nullptr && b->getCell(7, 2)->getPiece() == nullptr && b->getCell(7, 3)->getPiece() == nullptr) {
                    validMoves.push_back(b->getCell(7, 2));
                }
            }
            Piece* rook2 = b->getCell(7, 7)->getPiece();
            if (rook2 != nullptr && rook2->getPieceType() == PieceType::WhiteRook && !(rook2->getHasMoved())) {
                if (b->getCell(7, 6)->getPiece() == nullptr && b->getCell(7, 5)->getPiece() == nullptr) {
                    validMoves.push_back(b->getCell(7, 6));
                }
            }
        }
    }
}