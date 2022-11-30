#include "rook.h"
#include "piececolor.h"
#include "square.h"

Rook::Rook(PieceColor color, Square *pos)
: color{color}, pos{pos} {}