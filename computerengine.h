#ifndef __COMPUTERENGINE_H__
#define __COMPUTERENGINE_H__
#include "move.h"
#include "board.h"
#include "piececolor.h"

class ComputerEngine {
    public:
        ComputerEngine(int level);
        Move makeMove(Board* board, PieceColor color);
    private:
        int level;
}

#endif