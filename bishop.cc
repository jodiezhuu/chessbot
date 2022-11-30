#include "bishop.h"
#include "square.h"
#include "piececolor.h"

Bishop::Bishop(PieceColor color, Square *pos)
: color{color}, pos{pos} {}
