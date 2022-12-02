#include "game.h"
#include "Pieces/piece.h"
#include "computerengine.h"
#include <string>
#include <iostream>

Game::Game(): ongoing{false}, turn{PieceColor::White}, status{CheckStatus::None}, result{Result::Ongoing} {
    board = new Board{};
    scores[0] = 0;
    scores[1] = 0;
}

Game::~Game() {
    delete board;
}

PieceType Game::getState(int row, int col) {
    Piece * piece= board->getCell(row, col)->getPiece();
    if (piece == nullptr) {
        return PieceType::Empty;
    }
    return piece->getPieceType();
}

bool Game::addPiece(std::string type, std::string location) {
    std::cout << "adding piece in game" << std::endl;
    std::cout << location[0] << "_" << location[1] << std::endl;
    int col = location[0] - 'a';
    int row = 8 - (location[1] - '0');
    std::cout << "row: " << row << " col: " << col << " type: " << (int) convertChar(type[0]) << std::endl;
    bool res = board->addPiece(row, col, convertChar(type[0]));
    std::cout << "here" << std::endl;
    notifyObservers();
    return res;
}

void Game::removePiece(std::string location) {
    std::cout << "removing piece in game" << std::endl;
    int col = location[0] - 'a';
    int row = 8 - (location[1] - '0');
    std::cout << "row: " << row << " col: " << col << std::endl;
    board->removePiece(row, col);
    notifyObservers();
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
    reset();
}

void Game::reset() {
    turn = PieceColor::White;
    status = CheckStatus::None;
    result = Result::Ongoing;
    board->resetBoard();
    ongoing = false;
    delete players[0];
    delete players[1];
}

bool Game::verifySetup() {
    return board->verifyBoard();
}

void Game::startGame(std::string playerOneType, std::string playerTwoType) {
    if (playerOneType  == "human") {
        players[0] = new Player{PieceColor::White, false};
    } else if (playerOneType == "computer1") {
        players[0] = new Player{PieceColor::White, true, new ComputerEngine{1}};
    } else if (playerOneType == "computer2") {
        players[0] = new Player{PieceColor::White, true, new ComputerEngine{2}};
    } else if (playerOneType == "computer3") {
        players[0] = new Player{PieceColor::White, true, new ComputerEngine{3}};
    } else if (playerOneType == "computer4") {
        players[0] = new Player{PieceColor::White, true, new ComputerEngine{4}};
    } else {
        std::cout << "Invalid parameter for white-player" << std::endl;
        return;
    }

    if (playerTwoType == "human") {
        players[1] = new Player{PieceColor::Black, false};
    } else if (playerTwoType == "computer1") {
        players[1] = new Player{PieceColor::Black, true, new ComputerEngine{1}};
    } else if (playerTwoType == "computer2") {
        players[1] = new Player{PieceColor::Black, true, new ComputerEngine{2}};
    } else if (playerTwoType == "computer3") {
        players[1] = new Player{PieceColor::Black, true, new ComputerEngine{3}};
    } else if (playerTwoType == "computer4") {
        players[1] = new Player{PieceColor::Black, true, new ComputerEngine{4}};
    } else {
        std::cout << "Invalid parameter for black-player" << std::endl;
        return;
    }
    ongoing = true;
}

bool Game::isComputer(PieceColor color) {
    return players[1 - (int) color]->getComputer();
}

PieceColor Game::getTurn() {
    return turn;
}

bool Game::move(std::string from, std::string to) {
    int fromCol = from[0] - 'a';
    int fromRow = 8 - (from[1] - '0');
    int toCol = to[0] - 'a';
    int toRow = 8 - (to[1] - '0');
    bool validMove = false;
    Piece * movedPiece = board->getCell(fromRow, fromCol)->getPiece();
    if (movedPiece == nullptr || movedPiece->getColor() != turn) {
        std::cout << "entered move is not valid" << std::endl;
        return false;
    }
    std::vector<Square*> moves = movedPiece->getValidMoves();
    for (auto m : moves) {
        if (toCol == m->getCol() && toRow == m->getRow()) {
            validMove = true;
            break;
        }
    }
    if (!validMove) {
        std::cout << "entered move is not valid" << std::endl;
        return false;
    }
    if ((movedPiece->getPieceType() == PieceType::WhiteKing || movedPiece->getPieceType() == PieceType::BlackKing) && abs(fromCol - toCol) > 1 ) {
        board->getCell(fromRow, fromCol)->setPiece(nullptr);
        board->getCell(toRow, toCol) ->setPiece(movedPiece);
        movedPiece->setPosition(toRow, toCol);
        movedPiece->setHasMoved(true);
        if (toCol == 6) {
            Piece * rook = board->getCell(fromRow, 7)->getPiece();
            board->getCell(fromRow, 7)->setPiece(nullptr);
            board->getCell(toRow, 5) ->setPiece(rook);
            rook->setPosition(toRow, 5);
            rook->setHasMoved(true);
        } else {
            Piece * rook = board->getCell(fromRow, 0)->getPiece();
            board->getCell(fromRow, 0)->setPiece(nullptr);
            board->getCell(toRow, 3) ->setPiece(rook);
            rook->setPosition(toRow, 3);
            rook->setHasMoved(true);
        }
    } else {
        board->getCell(fromRow, fromCol)->setPiece(nullptr);
        board->getCell(toRow, toCol) ->setPiece(movedPiece);
        movedPiece->setPosition(toRow, toCol);
        movedPiece->setHasMoved(true);
    }
    
    return true;
}

bool Game::move() {

}

bool Game::getGameState() const {
    return ongoing;
}