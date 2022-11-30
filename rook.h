#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"
class Rook: public Piece {
public:
    Rook(PieceColor color, Square *pos, PieceType type);
    // bool isMoveValid(int row, int col, PieceColor color, Board *b) override;
    // Square[] checkMoves(Board *b) override;
    // Square[] capturingMoves(Board *b) override; 
    // bool canBeCaptured(Board *b) override; 
};

#endif