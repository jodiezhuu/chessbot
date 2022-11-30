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

Square ** Pawn::validMoves() {
    int index = 0;
    int row = pos->getRow();
    int col = pos->getCol();
    Square ** moves;
    if (color == PieceColor::Black && (b->getCell(row + 1, col))->getPiece() == nullptr && row + 1 <= 8) {
        Square * m = b->getCell(row + 1, col);
        moves[index] = m;
        index++;
        moveNum++;
    }
    if (color == PieceColor::White && (b->getCell(row - 1, col))->getPiece() == nullptr && row - 1 >= 1) {
        Square * m = b->getCell(row - 1, col);
        moves[index] = m;
        index++;
        moveNum++;
    }
    if (color == PieceColor::Black && (b->getCell(row + 1, col - 1))->getPiece()->getColor() != color && row + 1 <= 8 && col - 1 >= 1) {
        Square * m = b->getCell(row + 1, col - 1);
        moves[index] = m;
        index++;
        moveNum++;
    } 
    if (color == PieceColor::Black && (b->getCell(row + 1, col + 1))->getPiece()->getColor() != color && row + 1 <= 8 && col + 1 <= 8) {
        Square * m = b->getCell(row + 1, col + 1);
        moves[index] = m;
        index++;
        moveNum++;
    }
    if (color == PieceColor::White && (b->getCell(row - 1, col + 1))->getPiece()->getColor() != color && row - 1 >= 1 && col + 1 <= 8) {
        Square * m = b->getCell(row - 1, col + 1);
        moves[index] = m;
        index++;
        moveNum++;
    }
    if (color == PieceColor::White && (b->getCell(row - 1, col - 1))->getPiece()->getColor() != color && row - 1 >= 1 && col - 1 >= 1) {
        Square * m = b->getCell(row - 1, col - 1);
        moves[index] = m;
        index++;
        moveNum++;
    }
    if (color == PieceColor::Black && row == 2 && (b->getCell(row + 2, col))->getPiece() == nullptr) {
        Square * m = b->getCell(row + 2, col);
        moves[index] = m;
        index++;
        moveNum++;
    }
    if (color == PieceColor::White && row == 7 && (b->getCell(row - 2, col))->getPiece() == nullptr) {
        Square * m = b->getCell(row - 2, col);
        moves[index] = m;
        index++;
        moveNum++;
    }
    return moves;
}

Square ** Pawn::capturingMoves() {
    int index = 0;
    int row = pos->getRow();
    int col = pos->getCol();
    Square ** captures;
    if (color == PieceColor::Black && (b->getCell(row + 1, col - 1))->getPiece()->getColor() != color && row + 1 <= 8 && col - 1 >= 1) {
        Square * m = b->getCell(row + 1, col - 1);
        captures[index] = m;
        index++;
    } 
    if (color == PieceColor::Black && (b->getCell(row + 1, col + 1))->getPiece()->getColor() != color && row + 1 <= 8 && col + 1 <= 8) {
        Square * m = b->getCell(row + 1, col + 1);
        captures[index] = m;
        index++;
    }
    if (color == PieceColor::White && (b->getCell(row - 1, col + 1))->getPiece()->getColor() != color && row - 1 >= 1 && col + 1 <= 8) {
        Square * m = b->getCell(row - 1, col + 1);
        captures[index] = m;
        index++;
    }
    if (color == PieceColor::White && (b->getCell(row - 1, col - 1))->getPiece()->getColor() != color && row - 1 >= 1 && col - 1 >= 1) {
        Square * m = b->getCell(row - 1, col - 1);
        captures[index] = m;
        index++;
    }
    return captures;
}
