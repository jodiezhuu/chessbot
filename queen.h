#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "board.h"
#include "piececolor.h"
#include "square.h"
class Queen: public Piece {
    PieceColor color;
    Square *pos;
public:
    Queen(PieceColor color, Square *pos);
    bool isMoveValid(int row, int col, PieceColor color, Board *b) override;
    Square[] checkMoves(Board *b) override;
    Square[] capturingMoves(Board *b) override; 
    bool canBeCaptured(Board *b) override;
};

#endif