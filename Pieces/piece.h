#ifndef __PIECE_H__
#define __PIECE_H__
#include "piececolor.h"
#include "../square.h"
#include "piecetype.h"
#include "piecelist.h"
#include "../board.h"
#include <vector>

class Piece {
protected:
    PieceColor color;
    Square *pos;
    PieceType type;
    Board *b;
    std::vector <Square *> validMoves;
    std::vector <Square *> capturingMoves;
    bool inBound(int row, int col);
public:
    Piece(Board *b, PieceColor color, Square *pos, PieceType type);
    PieceType getPieceType() const;
    PieceColor getColor() const;
    Square *getPosition() const;
    virtual bool isMoveValid(int row, int col) = 0;
    std::vector <Square *> getValidMoves() const;
    std::vector <Square *> getCapturingMoves() const;
    virtual void calculateValidMoves() = 0;
    virtual void calculateCapturingMoves() = 0; 
    virtual bool canBeCaptured() = 0; 
    ~Piece() {};  
};

#endif