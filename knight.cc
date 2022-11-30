#include "knight.h"
#include "piececolor.h"
#include "square.h"

Knight::Knight(PieceColor color, Square *pos)
: color{color}, pos{pos} {}