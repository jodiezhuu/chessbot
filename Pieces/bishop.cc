#include "bishop.h"
#include <iostream>

Bishop::Bishop(Board *b, PieceColor color, Square *pos, PieceType type)
: Piece{b, color, pos, type} {}

void Bishop::calculateMoves() {
    validMoves.clear();
    capturingMoves.clear();
    // left-up diagonal
    for (int i = 1; i <= 7; ++i) {
        std::cout << "{" << pos->getRow() - i << "," << pos->getCol() -i << "} ";
        if (!inBound(pos->getRow() - i, pos->getCol() - i)) break;
        Square * sq = b->getCell(pos->getRow() - i, pos->getCol() - i);
        Piece *piece = sq->getPiece();
        if (piece == nullptr) {
            validMoves.push_back(sq);
        } else if (piece->getColor() == color) {
            std::cout << "??? ";
            break;
        } else if (piece->getColor() != color) {
            std::cout << "here ";
            validMoves.push_back(sq);
            capturingMoves.push_back(sq);
            break;
        }
    }
    std::cout << std::endl;

    // right-up diagonal
    for (int i = 1; i <= 7; ++i) {
        std::cout << "{" << pos->getRow() - i << "," << pos->getCol() + i << "} ";
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
    std::cout << std::endl;
    // left-down diagonal
    for (int i = 1; i <= 7; ++i) {
        std::cout << "{" << pos->getRow() + i << "," << pos->getCol() - i << "} ";
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
    std::cout << std::endl;
    // right-down diagonal
    for (int i = 1; i <= 7; ++i) {
        std::cout << "{" << pos->getRow() + i << "," << pos->getCol() + i << "} ";
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
    std::cout << std::endl;
}