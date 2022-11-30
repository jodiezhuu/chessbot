#include "pawn.h"
#include "square.h"

Pawn::Pawn(Board *b, PieceColor color, Square *pos, PieceType type)
: Piece{b, color, pos, type} {}

bool Pawn::isMoveValid(int row, int col) {
    if (moveNum > 0) {
        return true;
    }
    return false;
}

std::vector <Square *> Pawn::validMoves() {
    int row = pos->getRow();
    int col = pos->getCol();
    std::vector <Square *> moves;
    if (color == PieceColor::Black) {
        if ((b->getCell(row + 1, col))->getPiece() == nullptr && row + 1 <= 8) {
            Square * m = b->getCell(row + 1, col);
            moves.emplace_back(m);
            moveNum++;
        }
        if ((b->getCell(row + 1, col - 1))->getPiece() != nullptr && (b->getCell(row + 1, col - 1))->getPiece()->getColor() != color && row + 1 <= 8 && col - 1 >= 1) {
            Square * m = b->getCell(row + 1, col - 1);
            moves.emplace_back(m);
            moveNum++;
        }
        if ((b->getCell(row + 1, col + 1))->getPiece() != nullptr && (b->getCell(row + 1, col + 1))->getPiece()->getColor() != color && row + 1 <= 8 && col + 1 <= 8) {
            Square * m = b->getCell(row + 1, col + 1);
            moves.emplace_back(m);
            moveNum++;
        }
        if ((b->getCell(row + 1, col + 1))->getPiece() != nullptr && (b->getCell(row + 1, col + 1))->getPiece()->getColor() != color && row + 1 <= 8 && col + 1 <= 8) {
            Square * m = b->getCell(row + 1, col + 1);
            moves.emplace_back(m);
            moveNum++;
        }
        if (row == 2 && (b->getCell(row + 2, col))->getPiece() == nullptr) {
            Square * m = b->getCell(row + 2, col);
            moves.emplace_back(m);
            moveNum++;
        }
    } else if (color == PieceColor::White) {
        if ((b->getCell(row - 1, col))->getPiece() == nullptr && row - 1 >= 1) {
            Square * m = b->getCell(row - 1, col);
            moves.emplace_back(m);
            moveNum++;
        }
        if ((b->getCell(row - 1, col + 1))->getPiece() != nullptr && (b->getCell(row - 1, col + 1))->getPiece()->getColor() != color && row - 1 >= 1 && col + 1 <= 8) {
            Square * m = b->getCell(row - 1, col + 1);
            moves.emplace_back(m);
            moveNum++;
        }
        if ((b->getCell(row - 1, col - 1))->getPiece() != nullptr && (b->getCell(row - 1, col - 1))->getPiece()->getColor() != color && row - 1 >= 1 && col - 1 >= 1) {
            Square * m = b->getCell(row - 1, col - 1);
            moves.emplace_back(m);
            moveNum++;
        }
        if (row == 7 && (b->getCell(row - 2, col))->getPiece() == nullptr) {
            Square * m = b->getCell(row - 2, col);
            moves.emplace_back(m);
            moveNum++;
        }
    }
    return moves;
}

std::vector <Square *> Pawn::capturingMoves() {
    int row = pos->getRow();
    int col = pos->getCol();
    std::vector <Square *> captures;
    if (color == PieceColor::Black) {
        if ((b->getCell(row + 1, col - 1))->getPiece() != nullptr && (b->getCell(row + 1, col - 1))->getPiece()->getColor() != color && row + 1 <= 8 && col - 1 >= 1) {
            Square * m = b->getCell(row + 1, col - 1);
            captures.emplace_back(m);
        } 
        if ((b->getCell(row + 1, col + 1))->getPiece() != nullptr && (b->getCell(row + 1, col + 1))->getPiece()->getColor() != color && row + 1 <= 8 && col + 1 <= 8) {
            Square * m = b->getCell(row + 1, col + 1);
            captures.emplace_back(m);
        }
    } else if (color == PieceColor::White) {
        if ((b->getCell(row - 1, col + 1))->getPiece() != nullptr && (b->getCell(row - 1, col + 1))->getPiece()->getColor() != color && row - 1 >= 1 && col + 1 <= 8) {
            Square * m = b->getCell(row - 1, col + 1);
            captures.emplace_back(m);
        }
        if ((b->getCell(row - 1, col - 1))->getPiece() != nullptr && (b->getCell(row - 1, col - 1))->getPiece()->getColor() != color && row - 1 >= 1 && col - 1 >= 1) {
            Square * m = b->getCell(row - 1, col - 1);
            captures.emplace_back(m);
        }
    }
    return captures;
}
