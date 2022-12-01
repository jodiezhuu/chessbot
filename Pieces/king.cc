#include "king.h"

King::King(Board *b, PieceColor color, Square *pos, PieceType type) 
: Piece{b, color, pos, type} {}

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

bool King::isMoveValid(int row, int col) {
    int posRow = pos->getRow();
    int posCol = pos->getCol();

    if ((posRow - 1 <= row && row <= posRow + 1) && (posCol - 1 <= col && col <= posCol + 1) && posCol != col && posRow != row) {
        return !moveInCheck(row, col);
    }
    return false;
}

// std::vector <Square *> King::validMoves() {
//     std::vector <Square *> res;
//     int posRow = pos->getRow();
//     int posCol = pos->getCol();
//     for (int row = posRow - 1; row <= posRow + 1; ++row) {
//         for (int col = posCol - 1; col <= posCol + 1; ++col) {
//             if (!(inBound(row, col) && (row != posRow && col != posCol))) continue;
//             if (!moveInCheck(row, col)) {
//                 res.emplace_back(b->getCell(row, col));
//             }
//         }
//     }
// }

// std::vector <Square *> King::capturingMoves() {

// } 

bool King::canBeCaptured() {
    return moveInCheck(pos->getRow(), pos->getCol());
}