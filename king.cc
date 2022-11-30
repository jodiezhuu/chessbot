#include "king.h"
#include "piececolor.h"
#include "square.h"

King::King(PieceColor color, Square *pos) 
: color{color}, pos{pos} {}