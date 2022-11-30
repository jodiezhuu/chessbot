#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"
class Queen: public Piece {
public:
    Queen(Board *b, PieceColor color, Square *pos, PieceType type);
    // bool isMoveValid(int row, int col, PieceColor color, Board *b) override;
    // Square[] validMoves(Board *b) override;
    // Square[] capturingMoves(Board *b) override; 
    // bool canBeCaptured(Board *b) override;
};

#endif