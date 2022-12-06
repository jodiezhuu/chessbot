#include "player.h"

// player constructor
Player::Player(PieceColor color, bool computer, ComputerEngine* engine) 
: color{color}, computer{computer}, engine{engine} {}

// accessor for color
PieceColor Player::getColor() {
    return color;
}

// mutator for color
void Player::setColor(PieceColor newcolor) {
    color = newcolor;
}

// accessor for computer
bool Player::getComputer() {
    return computer;
}

// mutator for computer
void Player::setComputer(bool newcomputer) {
    computer = newcomputer;
}

// accessor for ComputerEngine* engine
ComputerEngine* Player::getEngine() {
    return engine;
}

// mutator for ComputerEngine* engine
void Player::setEngine(ComputerEngine* newengine) {
    engine = newengine;
}

// player destructor
Player::~Player() {
    delete engine;
}