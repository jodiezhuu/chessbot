#include "game.h"
#include "Pieces/piece.h"
#include <string>
#include <iostream>

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

bool Game::addPiece(std::string type, std::string location) {
   int col = location[0] - 'a';
   int row = 8 - (int) location[1];
//    board->addPiece(row, col, convertChar(type[0]))
}

bool Game::removePiece(std::string location) {
   int col = location[0] - 'a';
   int row = 8 - (int) location[1];
   board->removePiece(row, col);
}

void Game::setTurn(std::string colour) {
    if (colour == "white") {
        turn = PieceColor::White;
    } else if (colour == "black") {
        turn = PieceColor::Black;
    }
}

PieceType Game::convertChar(char c) {
    if (c == 'b') {
        return PieceType::BlackBishop;
    } else if (c == 'k') {
        return PieceType::BlackKing;
    } else if (c == 'n') {
        return PieceType::BlackKnight;
    } else if (c == 'p') {
        return PieceType::BlackPawn;
    } else if (c == 'q') {
        return PieceType::BlackQueen;
    } else if (c == 'r') {
        return PieceType::BlackRook;
    } else if (c == 'B') {
        return PieceType::WhiteBishop;
    } else if (c == 'K') {
        return PieceType::WhiteKing;
    } else if (c == 'N') {
        return PieceType::WhiteKnight;
    } else if (c == 'P') {
        return PieceType::WhitePawn;
    } else if (c == 'Q') {
        return PieceType::WhiteQueen;
    } else if (c == 'R') {
        return PieceType::WhiteRook;
    }
}

void Game::printScore() {
    std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << scores[0] << std::endl;
    std::cout << "Black: " << scores[1] << std::endl;
}

void Game::resign() {
    if (turn == PieceColor::White) {
        scores[1] += 1;
    } else if (turn == PieceColor::Black) {
        scores[0] += 1;
    }
    // reset();
}