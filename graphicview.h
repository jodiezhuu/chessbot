#ifndef __GRAPHICVIEW_H__
#define __GRAPHICVIEW_H__
#include "observer.h"
#include "game.h"
#include "Pieces/piecetype.h"
#include <iostream>
#include "window.h"

class GraphicView: public Observer {
    Game *game;
    Xwindow window;
    void drawPiece(PieceType type, int x, int y);
    PieceType pieceBoard[8][8];
public:
    GraphicView(Game *game);
    void notify() override;
    ~GraphicView();
};

#endif