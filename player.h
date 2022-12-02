#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Pieces/piececolor.h"
#include "computerengine.h"

class ComputerEngine;

class Player {
    public:
        Player(PieceColor color, bool computer, ComputerEngine* engine = nullptr);
        PieceColor getColor();
        void setColor(PieceColor newcolor);
        bool getComputer();
        void setComputer(bool newcomputer);
        ComputerEngine* getEngine();
        void setEngine(ComputerEngine* newengine);
        ~Player();
    private:
        PieceColor color;
        bool computer;
        ComputerEngine* engine;
};

#endif