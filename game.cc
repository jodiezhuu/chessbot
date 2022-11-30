#include "game.h"
#include "Pieces/piece.h"

Game::Game(): finished{false}, turn{PieceColor::White}, status{CheckStatus::None}, result{Result::Ongoing} {
    board = new Board{};
    scores[0] = 0;
    scores[1] = 0;
}

Game::~Game() {
    delete board;
}

void Game::render() {
    notifyObservers();
}

PieceType Game::getState(int row, int col) {
    Piece * piece= board->getCell(row, col)->getPiece();
    if (piece == nullptr) {
        return PieceType::Empty;
    }
    return piece->getPieceType();
}

//bool Game::addPiece(std::string type, std::string location) {
//    int row = location[0] - 'a';
//    int col = (int) location[1] - 1;
//}
//
//bool Game::removePiece(std::string location) {
//    int row = location[0] - 'a';
//    int col = (int) location[1] - 1;
//}