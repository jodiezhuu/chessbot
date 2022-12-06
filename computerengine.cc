#include "computerengine.h"
#include "Pieces/piecelist.h"
#include "Pieces/piece.h"
#include <iostream>
#include <cstdlib>
#include <random>

ComputerEngine::ComputerEngine(int level) : level{level} {
    moveCount = 0;
    opening = 0;
}

Move* ComputerEngine::makeMove(Board* board, PieceColor color) {
     // Create a random number generator
    std::default_random_engine generator;

    // Generate a random number between 1 and 10
    std::uniform_int_distribution<int> distribution(1, 10000000);
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
                    for (auto move : piece->getValidMoves()) {
                        moves.push_back(new Move(piece->getPosition(), move, piece));
                        std::cout << "pushed!" << std::endl;
                    }
                }
                std::cout << "size: " << moves.size() << std::endl;
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
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    std::vector<Square*> capturemoves = piece->getCapturingMoves();
                    std::cout << "captures: " << capturemoves.size() << std::endl;
                    std::vector<Square*> checkmoves = piece->getDeliverChecks();
                    std::cout << "checks: " << checkmoves.size() << std::endl;
                    for (auto move : validmoves) {
                        moves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                    for (auto move : capturemoves) {
                        captureCheckMoves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                    for (auto move : checkmoves) {
                        captureCheckMoves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                }
                std::cout << "capturesize: " << captureCheckMoves.size() << std::endl;
                if (captureCheckMoves.size() != 0) {
                    int num = rand() % captureCheckMoves.size();
                    return captureCheckMoves.at(num);
                } else {
                    int num = rand() % moves.size();
                    return moves.at(num);
                }
            }
        case 3:
            {
                std::cout << "is this running" << std::endl;
                std::vector<Piece*> * list;
                if (color == PieceColor::White) {
                    list = board->getWhitePieces()->getPieces();
                } else {
                    list = board->getBlackPieces()->getPieces();
                }
                std::vector<Move*> moves;
                std::vector<Move*> preferredMoves;
                for (auto piece : *list) {
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    for (auto move : validmoves) {
                        moves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                    validmoves.clear();
                    std::vector<Square*> capturemoves = piece->getCapturingMoves();
                    for (auto move : capturemoves) {
                        preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                    capturemoves.clear();
                }
                std::vector<Piece*> * newlist;
                std::vector<Square*> otherColorMoves;
                if (color == PieceColor::Black) {
                    newlist = board->getWhitePieces()->getPieces();
                } else {
                    newlist = board->getBlackPieces()->getPieces();
                }

                for (auto piece : *newlist) {
                    std::vector<Square*> othermoves;
                    if (piece->getPieceType() == PieceType::WhitePawn || piece->getPieceType() == PieceType::BlackPawn) {
                        othermoves = piece->getMovesToCapture();
                    } else {
                        othermoves = piece->getValidMoves();
                    }
                    for (auto move : othermoves) {
                        otherColorMoves.push_back(move);
                        std::cout << "OCRow: " << move->getRow() << "|OCCol: " << move->getCol() << std::endl;
                    }
                }
                for (auto piece : *list) {
                    bool safe = true;
                    if (!piece->canBeCaptured()) continue;
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    for (auto move : validmoves) {
                        bool safe = true;
                        for (auto otherMove : otherColorMoves) {
                            if (move == otherMove) {
                                //std::cout << "Row: " << move->getRow() << "|Col: " << move->getCol() << std::endl;
                                safe = false;
                            }
                        }
                        //std::cout << "safe?: " << (bool) safe << std::endl;
                        if (safe) {
                            preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                        }
                    }
                    validmoves.clear();
                }
                std::cout << "preferredmoves" << std::endl;
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
                break;
            }
        case 4:
            {
                if (moveCount == 0) {
                    //opening = rand() % 5;
                }

                std::vector<Piece*> * list;
                if (color == PieceColor::White) {
                    list = board->getWhitePieces()->getPieces();
                } else {
                    list = board->getBlackPieces()->getPieces();
                }
                std::vector<Move*> moves;
                for (auto piece : *list) {
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    for (auto move : validmoves) {
                        moves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                }
                Move * testmove;
                //std::cout << "movecount: " << moveCount << std::endl;
                //std::cout << "opening: " << opening << std::endl;
                if (moveCount < 5) {
                    testmove = playOpening(board);
                    // std::cout << "FRow: " << testmove->getFrom()->getRow() << "|FCol: " << testmove->getFrom()->getCol() << "|TRow: " << testmove->getTo()->getRow() << "|TCol: " << testmove->getTo()->getCol() << std::endl;
                    // std::cout << "size: " << moves.size() << std::endl;
                    for (auto move : moves) {
                        // std::cout << "FRow: " << move->getFrom()->getRow() << "|FCol: " << move->getFrom()->getCol() << "|TRow: " << move->getTo()->getRow() << "|TCol: " << move->getTo()->getCol() << std::endl;
                        if (move->getFrom()->getRow() == testmove->getFrom()->getRow() && move->getFrom()->getCol() == testmove->getFrom()->getCol() && move->getTo()->getCol() == testmove->getTo()->getCol() && move->getTo()->getRow() == testmove->getTo()->getRow()) {
                            // std::cout << "success" << std::endl;
                            ++moveCount;
                            return testmove;
                        }
                    }
                }
                std::vector<Move*> preferredMoves;
                std::vector<Move*> forks;
                std::vector<Move*> attacks;
                for (auto piece : *list) {
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    // for (auto move : validmoves) {
                    //     Square *old = piece->getPosition();
                    //     piece->setPosition(move->getRow(), move->getCol());
                    //     if (piece->getCapturingMoves().size() > 1) {
                    //         forks.push_back(new Move(old, move, piece));
                    //     } else if (piece->getCapturingMoves().size() > 0) {
                    //         attacks.push_back(new Move(old, move, piece));
                    //     }
                    //     piece->setPosition(old->getRow(), old->getCol());
                    // }
                    validmoves = piece->getCapturingMoves();
                    for (auto move : validmoves) {
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
                    std::vector<Square*> othermoves;
                    if (piece->getPieceType() == PieceType::WhitePawn || piece->getPieceType() == PieceType::BlackPawn) {
                        othermoves = piece->getMovesToCapture();
                    } else {
                        othermoves = piece->getValidMoves();
                    }
                    for (auto move : othermoves) {
                        otherColorMoves.push_back(move);
                        //std::cout << "OCRow: " << move->getRow() << "|OCCol: " << move->getCol() << std::endl;
                    }
                }

                for (auto piece : *list) {
                    bool safe = true;
                    if (!piece->canBeCaptured()) continue;
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    for (auto move : validmoves) {
                        bool safe = true;
                        for (auto otherMove : otherColorMoves) {
                            if (move == otherMove) {
                                //std::cout << "Row: " << move->getRow() << "|Col: " << move->getCol() << std::endl;
                                safe = false;
                            }
                        }
                        //std::cout << "safe?: " << (bool) safe << std::endl;
                        if (safe) {
                            preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                        }
                    }
                }

                // for (auto move : preferredMoves) {
                //     std::cout << "FRow: " << move->getFrom()->getRow() << "|FCol: " << move->getFrom()->getCol() << "|TRow: " << move->getTo()->getRow() << "|TCol: " << move->getTo()->getCol() << std::endl;
                // }

                if (preferredMoves.size() != 0) {
                    int num = rand() % preferredMoves.size();
                    ++moveCount;
                    return preferredMoves.at(num);
                } else if (forks.size() != 0) {
                    int num = rand() % forks.size();
                    ++moveCount;
                    return forks.at(num);
                } else if (attacks.size() != 0) {
                    int num = rand() % attacks.size();
                    ++moveCount;
                    return attacks.at(num);
                } else {
                    int num = rand() % moves.size();
                    ++moveCount;
                    return moves.at(num);
                }
            }
    }
}

void ComputerEngine::setMoveCount(int count) {
    moveCount = count;
}

Move* ComputerEngine::playOpening(Board* board) {
    switch (opening) {
        case 0: 
        {
            switch(moveCount) {
                case 0:
                    return new Move(board->getCell(1, 4), board->getCell(3, 4), board->getCell(1, 4)->getPiece());
                case 1:
                    return new Move(board->getCell(0, 1), board->getCell(2, 2), board->getCell(0, 1)->getPiece());
                case 2:
                    return new Move(board->getCell(0, 6), board->getCell(2, 5), board->getCell(0, 6)->getPiece());
                case 3:
                    return new Move(board->getCell(0, 5), board->getCell(3, 2), board->getCell(0, 5)->getPiece());
                case 4:
                    return new Move(board->getCell(0, 4), board->getCell(0, 6), board->getCell(0, 4)->getPiece());
            }

        }
    }
}