#include "game.h"
#include "Pieces/piece.h"
#include "computerengine.h"
#include <string>
#include <iostream>

Game::Game(): ongoing{false}, turn{PieceColor::White}, status{CheckStatus::None} {
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
        std::cout << "Black wins!" << std::endl;
    } else if (turn == PieceColor::Black) {
        scores[0] += 1;
        std::cout << "White wins!" << std::endl;
    }
    reset();
}

void Game::reset() {
    turn = PieceColor::White;
    status = CheckStatus::None;
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
    Piece *old = board->getCell(toRow, toCol)->getPiece();
    if (movedPiece == nullptr || movedPiece->getColor() != turn) {
        std::cout << "Entered move is not valid" << std::endl;
        return false;
    }
    validMove = movedPiece->isMoveValid(toRow, toCol);

    if (!validMove) {
        std::cout << "Entered move is not valid" << std::endl;
        return false;
    }

    // Return false if move causes king to be in check
    if (movedPiece->getPieceType() == PieceType::WhiteKing || movedPiece->getPieceType() == PieceType::BlackKing) {
        // Move king
        board->getCell(fromRow, fromCol)->setPiece(nullptr);
        board->getCell(toRow, toCol)->setPiece(movedPiece);
        movedPiece->setPosition(toRow, toCol);
        // Check if king is in check
        if (movedPiece->canBeCaptured()) {
            // If in check move king back
            board->getCell(fromRow, fromCol)->setPiece(movedPiece);
            board->getCell(toRow, toCol)->setPiece(old);
            movedPiece->setPosition(fromRow, fromCol);
            return false;
        } else {
            movedPiece->setHasMoved(true);
        }
    }

    // Castling
    if ((movedPiece->getPieceType() == PieceType::WhiteKing || movedPiece->getPieceType() == PieceType::BlackKing) && abs(fromCol - toCol) > 1 ) {
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
    } else if (!(movedPiece->getPieceType() == PieceType::WhiteKing || movedPiece->getPieceType() == PieceType::BlackKing)) { // Normal moves
        board->getCell(fromRow, fromCol)->setPiece(nullptr);
        board->getCell(toRow, toCol)->setPiece(movedPiece);
        movedPiece->setPosition(toRow, toCol);
        movedPiece->setHasMoved(true);
    }

    // if move made doesn't get rid of check then invalid
    if ((status == CheckStatus::WhiteInCheck || status == CheckStatus::BlackInCheck) && status == calculateStatus()) {
        board->getCell(fromRow, fromCol)->setPiece(movedPiece);
        board->getCell(toRow, toCol)->setPiece(old);
        movedPiece->setPosition(fromRow, fromCol);
        std::cout << "Your king is in check!" << std::endl;
        return false;
    }

    // delete old piece if exists
    if (old != nullptr) {
        board->removePiece(old);
    }
    return true;
}

// For computer
bool Game::move() {

}

Game::CheckStatus Game::calculateStatus() {
    Piece *blackKing = board->getBlackKing();
    Piece *whiteKing = board->getWhiteKing();
    if (whiteKing->canBeCapturedIgnoreCheck()) {
        if (whiteKing->getValidMoves().empty()) {
            return CheckStatus::WhiteCheckmated;
        } else {
            return CheckStatus::WhiteInCheck;
        }
    } else if (blackKing->canBeCapturedIgnoreCheck()) {
        if (blackKing->getValidMoves().empty()) {
            return CheckStatus::BlackCheckmated;
        } else {
            return CheckStatus::BlackInCheck;
        }
    }
    std::vector <Piece *> *list;
    if (turn == PieceColor::Black) {
        list = board->getBlackPieces()->getPieces();
    } else {
        list = board->getWhitePieces()->getPieces();
    }
    for (auto piece : *list) {
        if (!piece->getValidMoves().empty()) return CheckStatus::None;
    }
    return CheckStatus::Stalemate; 
}

void Game::applyStatus() {
    status = calculateStatus();
    if (status == CheckStatus::WhiteCheckmated) {
        reset();
        scores[1] += 1;
        std::cout << "Checkmate! Black wins!" << std::endl;
    } else if (status == CheckStatus::BlackCheckmated) {
        reset();
        scores[0] += 1;
        std::cout << "Checkmate! White wins!" << std::endl;
    } else if (status == CheckStatus::WhiteInCheck) {
        std::cout << "White is in check" << std::endl;
    } else if (status == CheckStatus::BlackInCheck) {
        std::cout << "Black is in check" << std::endl;
    } else if (status == CheckStatus::Stalemate) {
        std::cout << "Stalemate!" << std::endl;
        reset();
        scores[0] += 0.5;
        scores[1] += 0.5;
    }
}

bool Game::isOngoing() const {
    return ongoing;
}

bool Game::isPawnUpgrading(std::string to) {
    int toCol = to[0] - 'a';
    int toRow = 8 - (to[1] - '0');
    PieceType piece = board->getCell(toRow, toCol)->getPiece()->getPieceType();
    if ((piece == PieceType::BlackPawn && toRow == 7) || (piece == PieceType::WhitePawn && toRow == 0)) {
        return true;
    } return false;
}

void Game::upgradePawn(PieceType type, std::string to) {
    int toCol = to[0] - 'a';
    int toRow = 8 - (to[1] - '0');
    PieceType piece = board->getCell(toRow, toCol)->getPiece()->getPieceType();
    if (piece == PieceType::BlackPawn && toRow == 7) {
        board->removePiece(toRow, toCol);
        if (type == PieceType::BlackBishop) {
            board->addPiece(toRow, toCol, PieceType::BlackBishop);
        } else if (type == PieceType::BlackQueen) {
            board->addPiece(toRow, toCol, PieceType::BlackQueen);
        } else if (type == PieceType::BlackKnight) {
            board->addPiece(toRow, toCol, PieceType::BlackKnight);
        } else if (type == PieceType::BlackRook) {
            board->addPiece(toRow, toCol, PieceType::BlackRook);
        }
    } else if (piece == PieceType::WhitePawn && toRow == 0) {
        board->removePiece(toRow, toCol);
        if (type == PieceType::WhiteBishop) {
            board->addPiece(toRow, toCol, PieceType::WhiteBishop);
        } else if (type == PieceType::WhiteKnight) {
            board->addPiece(toRow, toCol, PieceType::WhiteKnight);
        } else if (type == PieceType::WhiteRook) {            
            board->addPiece(toRow, toCol, PieceType::WhiteRook);
        } else if (type == PieceType::WhiteQueen) {
            board->addPiece(toRow, toCol, PieceType::WhiteQueen);
        }
    }
}