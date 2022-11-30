#ifndef __PIECE_H__
#define __PIECE_H__
#include "piececolor.h"
#include "../square.h"
#include "piecetype.h"
#include "../board.h"

class Piece {
protected:
    PieceColor color;
    Square *pos;
    PieceType type;
public:
    Piece(PieceColor color, Square *pos, PieceType type);
    PieceType getPieceType();
    PieceColor getColor();
    Square *getPosition();
    virtual bool isMoveValid(int row, int col, PieceColor color, Board *b) = 0;
    virtual Square ** checkMoves(PieceColor color, Board *b) = 0;
    virtual Square ** capturingMoves(PieceColor color, Board *b) = 0; 
    virtual bool canBeCaptured(Board *b) = 0; 
    ~Piece() {};  
};

#endif