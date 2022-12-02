#include "king.h"
#include "../square.h"
#include "rook.h"
#include <vector>
#include <iostream>

King::King(Board *b, PieceColor color, Square *pos, PieceType type) 
: Piece{b, color, pos, type} {
    hasMoved = false;
}

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

    //check for castling possibility
    if (!hasMoved) {
        //for black king
        if (color == PieceColor::Black) {
            //check both rooks
            Piece* rook1 = b->getCell(0, 0)->getPiece();
            if (rook1 != nullptr && rook1->getPieceType() == PieceType::BlackRook && !(rook1->getHasMoved())) {
                if (b->getCell(0, 1)->getPiece() == nullptr && b->getCell(0, 2)->getPiece() == nullptr && b->getCell(0, 3)->getPiece() == nullptr && !moveInCheck(0, 4) && !moveInCheck(0, 3) && !moveInCheck(0, 2)) {
                    validMoves.push_back(b->getCell(0, 2));
                }
            }
            Piece* rook2 = b->getCell(0, 7)->getPiece();
            if (rook2 != nullptr && rook2->getPieceType() == PieceType::BlackRook && !(rook2->getHasMoved())) {
                if (b->getCell(0, 6)->getPiece() == nullptr && b->getCell(0, 5)->getPiece() == nullptr && !moveInCheck(0, 6) && !moveInCheck(0, 5) && !moveInCheck(0, 4)) {
                    validMoves.push_back(b->getCell(0, 6));
                }
            }
        } else {
            //for white king check both rooks
            Piece* rook1 = b->getCell(7, 0)->getPiece();
            if (rook1 != nullptr && rook1->getPieceType() == PieceType::WhiteRook && !(rook1->getHasMoved())) {
                if (b->getCell(7, 1)->getPiece() == nullptr && b->getCell(7, 2)->getPiece() == nullptr && b->getCell(7, 3)->getPiece() == nullptr && !moveInCheck(7, 4) && !moveInCheck(7, 3) && !moveInCheck(7, 2)) {
                    validMoves.push_back(b->getCell(7, 2));
                }
            }
            Piece* rook2 = b->getCell(7, 7)->getPiece();
            if (rook2 != nullptr && rook2->getPieceType() == PieceType::WhiteRook && !(rook2->getHasMoved())) {
                if (b->getCell(7, 6)->getPiece() == nullptr && b->getCell(7, 5)->getPiece() == nullptr && !moveInCheck(7, 6) && !moveInCheck(7, 5) && !moveInCheck(7, 4)) {
                    validMoves.push_back(b->getCell(7, 6));
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