#include "queen.h"
#include "piececolor.h"
#include "board.h"
#include "square.h"

Queen::Queen(PieceColor color, Square *pos)
: color{color}, pos{pos} {}