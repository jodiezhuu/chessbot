#include "pawn.h"
#include "square.h"

Pawn::Pawn(PieceColor color, Square *pos, PieceType type)
: Piece{color, pos, type} {}

bool Pawn::isMoveValid(int row, int col, PieceColor color, Board *b) {
    if (color == PieceColor::White && (b->getCell(row, col))->getPiece() == nullptr && row == pos->getRow() + 1 && col == pos->getCol()) {
        return true;
    } else if (color == PieceColor::Black && (b->getCell(row, col))->getPiece() == nullptr && row == pos->getRow() - 1 && col == pos->getCol()) {
        return true;
    } else if (color == PieceColor::White && row == pos->getRow() + 1 && (col == pos->getCol() - 1 || col == pos->getCol() + 1) && b->getCell(row, col)->getPiece()->getColor() != color) {
        return true;
    } else if (color == PieceColor::Black && row == pos->getRow() - 1 && (col == pos->getCol() - 1 || col == pos->getCol() + 1) && b->getCell(row, col)->getPiece()->getColor() != color) {
        return true;
    }
    return false;
}

Square ** Pawn::checkMoves(PieceColor color, Board *b) {
    int index = 0;
    int row = pos->getRow();
    int col = pos->getCol();
    Square ** moves;
    if (color == PieceColor::White && (b->getCell(row + 1, col))->getPiece() == nullptr && row + 1 <= 8) {
        Square * m = b->getCell(row + 1, col);
        moves[index] = m;
        index++;
    }
    if (color == PieceColor::Black && (b->getCell(row - 1, col))->getPiece() == nullptr && row - 1 >= 1) {
        Square * m = b->getCell(row - 1, col);
        moves[index] = m;
        index++;
    }
    if (color == PieceColor::White && (b->getCell(row + 1, col - 1))->getPiece()->getColor() != color && row + 1 <= 8 && col - 1 >= 1) {
        Square * m = b->getCell(row + 1, col - 1);
        moves[index] = m;
        index++;
    } 
    if (color == PieceColor::White && (b->getCell(row + 1, col + 1))->getPiece()->getColor() != color && row + 1 <= 8 && col + 1 <= 8) {
        Square * m = b->getCell(row + 1, col + 1);
        moves[index] = m;
        index++;
    }
    if (color == PieceColor::Black && (b->getCell(row - 1, col + 1))->getPiece()->getColor() != color && row - 1 >= 1 && col + 1 <= 8) {
        Square * m = b->getCell(row - 1, col + 1);
        moves[index] = m;
        index++;
    }
    if (color == PieceColor::Black && (b->getCell(row - 1, col - 1))->getPiece()->getColor() != color && row - 1 >= 1 && col - 1 >= 1) {
        Square * m = b->getCell(row - 1, col - 1);
        moves[index] = m;
        index++;
    }
    if (color == PieceColor::White && row == 2 && (b->getCell(row + 2, col))->getPiece() == nullptr) {
        Square * m = b->getCell(row + 2, col);
        moves[index] = m;
        index++;
    }
    if (color == PieceColor::Black && row == 7 && (b->getCell(row - 2, col))->getPiece() == nullptr) {
        Square * m = b->getCell(row - 2, col);
        moves[index] = m;
        index++;
    }
    return moves;
}

Square ** Pawn::capturingMoves(PieceColor color, Board *b) {
    int index = 0;
    int row = pos->getRow();
    int col = pos->getCol();
    Square ** captures;
    if (color == PieceColor::White && (b->getCell(row + 1, col - 1))->getPiece()->getColor() != color && row + 1 <= 8 && col - 1 >= 1) {
        Square * m = b->getCell(row + 1, col - 1);
        captures[index] = m;
        index++;
    } 
    if (color == PieceColor::White && (b->getCell(row + 1, col + 1))->getPiece()->getColor() != color && row + 1 <= 8 && col + 1 <= 8) {
        Square * m = b->getCell(row + 1, col + 1);
        captures[index] = m;
        index++;
    }
    if (color == PieceColor::Black && (b->getCell(row - 1, col + 1))->getPiece()->getColor() != color && row - 1 >= 1 && col + 1 <= 8) {
        Square * m = b->getCell(row - 1, col + 1);
        captures[index] = m;
        index++;
    }
    if (color == PieceColor::Black && (b->getCell(row - 1, col - 1))->getPiece()->getColor() != color && row - 1 >= 1 && col - 1 >= 1) {
        Square * m = b->getCell(row - 1, col - 1);
        captures[index] = m;
        index++;
    }
    return captures;
}
