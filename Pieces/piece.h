#ifndef __PIECE_H__
#define __PIECE_H__
#include "piececolor.h"
#include "../square.h"
#include "piecetype.h"
#include "piecelist.h"
#include "../board.h"
#include <vector>

class Board;

class Piece {
protected:
    PieceColor color;
    Square *pos;
    PieceType type;
    Board *b;
    bool hasMoved;
    std::vector <Square *> validMoves;
    std::vector <Square *> capturingMoves;
    std::vector <Square *> capturingMovesWithCheck;
    bool inBound(int row, int col);
    std::vector <Square *> getCapturingMovesNoCheck();
public:
    char convertPiece(PieceType type);
    Piece(Board *b, PieceColor color, Square *pos, PieceType type, bool hasMoved = false);
    PieceType getPieceType() const;
    PieceColor getColor() const;
    Square *getPosition() const;
    bool getHasMoved() const;
    void setHasMoved(bool val);
    bool canBeCapturedIgnoreCheck();
    void setPosition(int newrow, int newcol);
    virtual void calculateAllMoves() = 0;
    void filterAllMoves();
    bool isMoveValid(int row, int col);
    std::vector <Square *> getValidMoves();
    std::vector <Square *> getCapturingMoves();
    bool canBeCaptured() const; 
    ~Piece();  
};

#endif