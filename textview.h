#ifndef _TEXTVIEW_H_
#define _TEXTVIEW_H_
#include "observer.h"
#include "game.h"
#include "Pieces/piecetype.h"
#include <iostream>

class TextView: public Observer {
    Game *game;
    std::ostream &out = std::cout;
    char convertPiece(PieceType type);
public:
    TextView(Game *game);
    void notify() override;
    ~TextView();
};

#endif
