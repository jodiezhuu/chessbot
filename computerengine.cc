#include "computerengine.h"
#include "Pieces/piecelist.h"
#include "Pieces/piece.h"
#include <iostream>

ComputerEngine::ComputerEngine(int level) : level{level} {}

Move* ComputerEngine::makeMove(Board* board, PieceColor color) {
    switch (level) {
        case 1:
            {
                std::vector<Piece*> * list;
                if (color == PieceColor::White) {
                    list = board->getWhitePieces()->getPieces();
                } else {
                    list = board->getBlackPieces()->getPieces();
                }
                std::vector<Move*> moves;
                for (auto piece : *list) {
                    for (auto move : piece->getValidMoves())
                    moves.push_back(new Move(piece->getPosition(), move, piece));
                }
                int num = rand() % moves.size();
                return moves.at(num);
            }
        case 2:
            {
                std::vector<Piece*> * list;
                if (color == PieceColor::White) {
                    list = board->getWhitePieces()->getPieces();
                } else {
                    list = board->getBlackPieces()->getPieces();
                }
                std::vector<Move*> moves;
                std::vector<Move*> captureCheckMoves;
                for (auto piece : *list) {
                    for (auto move : piece->getValidMoves()) {
                        moves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                    for (auto move : piece->getCapturingMoves()) {
                        captureCheckMoves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                }
                if (captureCheckMoves.size() != 0) {
                    int num = rand() % captureCheckMoves.size();
                    return captureCheckMoves.at(num);
                }
                else {
                    int num = rand() % moves.size();
                    return moves.at(num);
                }
            }
        case 3:
            {
                std::vector<Piece*> * list;
                if (color == PieceColor::White) {
                    list = board->getWhitePieces()->getPieces();
                } else {
                    list = board->getBlackPieces()->getPieces();
                }
                std::vector<Move*> moves;
                std::vector<Move*> preferredMoves;
                for (auto piece : *list) {
                    for (auto move : piece->getValidMoves()) {
                        moves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                    for (auto move : piece->getCapturingMoves()) {
                        preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                }
                std::vector<Piece*> * newlist;
                std::vector<Square*> otherColorMoves;
                if (color == PieceColor::Black) {
                    newlist = board->getWhitePieces()->getPieces();
                } else {
                    newlist = board->getBlackPieces()->getPieces();
                }

                for (auto piece : *newlist) {
                    for (auto move : piece->getValidMoves()) {
                        otherColorMoves.push_back(move);
                        std::cout << "OCRow: " << move->getRow() << "|OCCol: " << move->getCol() << std::endl;
                    }
                }

                for (auto piece : *list) {
                    bool safe = true;
                    if (!piece->canBeCaptured()) continue;
                    for (auto move : piece->getValidMoves()) {
                        bool safe = true;
                        for (auto otherMove : otherColorMoves) {
                            if (move == otherMove) {
                                std::cout << "Row: " << move->getRow() << "|Col: " << move->getCol() << std::endl;
                                safe = false;
                            }
                        }
                        std::cout << "safe?: " << (bool) safe << std::endl;
                        if (safe) {
                            preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                        }
                    }
                }

                for (auto move : preferredMoves) {
                    std::cout << "FRow: " << move->getFrom()->getRow() << "|FCol: " << move->getFrom()->getCol() << "|TRow: " << move->getTo()->getRow() << "|TCol: " << move->getTo()->getCol() << std::endl;
                }

                if (preferredMoves.size() != 0) {
                    int num = rand() % preferredMoves.size();
                    return preferredMoves.at(num);
                }
                else {
                    int num = rand() % moves.size();
                    return moves.at(num);
                }
            }
        case 4:
            //level 4 engine move making
            break;
    }
}