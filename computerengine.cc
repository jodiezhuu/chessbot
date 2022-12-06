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
                    }
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
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    std::vector<Square*> capturemoves = piece->getCapturingMoves();
                    std::vector<Square*> checkmoves = piece->getDeliverChecks();
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
                    std::vector<Square*> checkmoves = piece->getDeliverChecks();
                    for (auto move : checkmoves) {
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
                    }
                }
                for (auto piece : *list) {
                    if (!piece->canBeCaptured()) continue;
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    for (auto move : validmoves) {
                        bool safe = true;
                        for (auto otherMove : otherColorMoves) {
                            if (move == otherMove) {
                                safe = false;
                            }
                        }
                        if (safe) {
                            preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                        }
                    }
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
                    opening = (rand() % 3) + (int) color * 3;
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
                if (moveCount < 5) {
                    testmove = playOpening(board);
                    for (auto move : moves) {
                        if (move->getFrom()->getRow() == testmove->getFrom()->getRow() && move->getFrom()->getCol() == testmove->getFrom()->getCol() && move->getTo()->getCol() == testmove->getTo()->getCol() && move->getTo()->getRow() == testmove->getTo()->getRow()) {
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
                    for (auto move : validmoves) {
                        int fromRow = piece->getPosition()->getRow();
                        int fromCol = piece->getPosition()->getCol();
                        int toRow = move->getRow();
                        int toCol = move->getCol();
                        board->getCell(fromRow, fromCol)->setPiece(nullptr);
                        Piece *old = board->getCell(toRow, toCol)->getPiece();
                        board->getCell(toRow, toCol)->setPiece(piece);
                        piece->setPosition(toRow, toCol);
                        if (piece->getCapturingMoves().size() > 1) {
                            forks.push_back(new Move(board->getCell(fromRow, fromCol), move, piece));
                        } else if (piece->getCapturingMoves().size() > 0) {
                            attacks.push_back(new Move(board->getCell(fromRow, fromCol), move, piece));
                        }
                        board->getCell(fromRow, fromCol)->setPiece(piece);
                        board->getCell(toRow, toCol)->setPiece(old);
                        piece->setPosition(fromRow, fromCol);
                    }
                    validmoves = piece->getCapturingMoves();
                    for (auto move : validmoves) {
                        preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                    validmoves = piece->getDeliverChecks();
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
                                safe = false;
                            }
                        }
                        if (safe) {
                            preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                        }
                    }
                }
                
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
        case 1:
        {
            switch(moveCount) {
                case 0:
                    return new Move(board->getCell(0, 6), board->getCell(2, 5), board->getCell(0, 6)->getPiece());
                case 1:
                    return new Move(board->getCell(1, 6), board->getCell(2, 6), board->getCell(1, 6)->getPiece());
                case 2:
                    return new Move(board->getCell(0, 5), board->getCell(1, 6), board->getCell(0, 5)->getPiece());
                case 3:
                    return new Move(board->getCell(1, 3), board->getCell(2, 3), board->getCell(1, 3)->getPiece());
                case 4:
                    return new Move(board->getCell(0, 4), board->getCell(0, 6), board->getCell(0, 4)->getPiece());
            }
        }
        case 2:
        {
            switch(moveCount) {
                case 0:
                    return new Move(board->getCell(0, 6), board->getCell(2, 5), board->getCell(0, 6)->getPiece());
                case 1:
                    return new Move(board->getCell(1, 4), board->getCell(2, 4), board->getCell(1, 4)->getPiece());
                case 2:
                    return new Move(board->getCell(0, 5), board->getCell(1, 4), board->getCell(0, 5)->getPiece());
                case 3:
                    return new Move(board->getCell(1, 1), board->getCell(2, 1), board->getCell(1, 1)->getPiece());
                case 4:
                    return new Move(board->getCell(0, 2), board->getCell(2, 0), board->getCell(0, 2)->getPiece());
            }
        }
        case 3:
        {
            switch(moveCount) {
                case 0:
                    return new Move(board->getCell(6, 4), board->getCell(4, 4), board->getCell(6, 4)->getPiece());
                case 1:
                    return new Move(board->getCell(7, 6), board->getCell(5, 5), board->getCell(7, 6)->getPiece());
                case 2:
                    return new Move(board->getCell(7, 5), board->getCell(4, 2), board->getCell(7, 5)->getPiece());
                case 3:
                    return new Move(board->getCell(6, 3), board->getCell(5, 3), board->getCell(6, 3)->getPiece());
                case 4:
                    return new Move(board->getCell(7, 4), board->getCell(7, 6), board->getCell(7, 4)->getPiece());
            }
        }
        case 4:
        {
            switch(moveCount) {
                case 0:
                    return new Move(board->getCell(6, 3), board->getCell(4, 3), board->getCell(6, 3)->getPiece());
                case 1:
                    return new Move(board->getCell(7, 2), board->getCell(4, 5), board->getCell(7, 2)->getPiece());
                case 2:
                    return new Move(board->getCell(6, 4), board->getCell(5, 4), board->getCell(6, 4)->getPiece());
                case 3:
                    return new Move(board->getCell(7, 6), board->getCell(5, 5), board->getCell(7, 6)->getPiece());
                case 4:
                    return new Move(board->getCell(6, 2), board->getCell(5, 2), board->getCell(6, 2)->getPiece());
            }
        }
        case 5:
        {
        switch(moveCount) {
                case 0:
                    return new Move(board->getCell(6, 2), board->getCell(4, 2), board->getCell(6, 2)->getPiece());
                case 1:
                    return new Move(board->getCell(7, 1), board->getCell(5, 2), board->getCell(7, 1)->getPiece());
                case 2:
                    return new Move(board->getCell(6, 4), board->getCell(4, 4), board->getCell(6, 4)->getPiece());
                case 3:
                    return new Move(board->getCell(6, 6), board->getCell(5, 6), board->getCell(6, 6)->getPiece());
                case 4:
                    return new Move(board->getCell(4, 4), board->getCell(3, 4), board->getCell(4, 4)->getPiece());
            }
        }
    }
}