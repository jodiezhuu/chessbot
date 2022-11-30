#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piececolor.h"
#include "square.h"
class Bishop: public Piece {
    PieceColor color;
    Square *pos;
public:
    Bishop(PieceColor color, Square *pos);
    bool isMoveValid(int row, int col, PieceColor color, Board *b) override;
    Square[] checkMoves(Board *b) override;
    Square[] capturingMoves(Board *b) override; 
    bool canBeCaptured(Board *b) override; 
}

#endif