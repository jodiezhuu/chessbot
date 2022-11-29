#include "player.h"

Player::Player(PieceColor color, bool computer, ComputerEngine* engine = nullptr) 
: color{color}, computer{computer}, engine{engine} {

}

PieceColor Player::getColor() {
    return color;
}

void Player::setColor(PieceColor newcolor) {
    color = newcolor;
}

bool Player::getComputer() {
    return computer;
}

void Player::setComputer(bool newcomputer) {
    computer = newcomputer;
}

ComputerEngine* Player::getEngine() {
    return engine;
}

void Player::setEngine(ComputerEngine* newengine) {
    engine = newengine;
}

Player::~Player() {
    delete engine;
}