#include "pawn.h"
#include "board.h"
#include "square.h"
#include "piececolor.h"

Pawn::Pawn(PieceColor color, Square *pos)
: color{color}, pos{pos} {}

// bool Pawn::isMoveValid(int row, int col, PieceColor color, Board *b) {
//     if (color == White && (b->getCell(row, col))->getPiece() == nullptr && row == ++pos->row && col == pos->col) {
//         return true;
//     } else if (color == Black && (b->getCell(row, col))->getPiece() == nullptr && row == --pos->row && col == pos->col) {
//         return true;
//     } else if (color == White && row == ++pos->row && (col == --pos->col || col == ++pos->col) && b->getCell(row, col)->getPiece()->getColor() != color) {
//         return true;
//     } return false;
// }