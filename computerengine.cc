#include "computerengine.h"
#include "piecelist.h"
#include "piece.h"

ComputerEngine::ComputerEngine(int level) : level{level} {}

Move ComputerEngine::makeMove(Board* board, PieceColor color) {
    switch (level) {
        case 1:
            //level 1 engine move making
            break;
        case 2:
            //level 2 engine move making
            break;
        case 3:
            //level 3 engine move making
            break;
        case 4:
            //level 4 engine move making
            break;
    }
}