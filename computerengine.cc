#include "computerengine.h"
#include "Pieces/piecelist.h"
#include "Pieces/piece.h"
#include <iostream>
#include <cstdlib>
#include <random>

// ComputerEngine constructor
ComputerEngine::ComputerEngine(int level) : level{level} {
    moveCount = 0;
    opening = 0;
}

// returns a Move object of the move selected by the engine
Move* ComputerEngine::makeMove(Board* board, PieceColor color) {
    // for each possible level
    switch (level) {
        case 1:
            {
                // gather a list of all pieces of the correct colour
                std::vector<Piece*> * list;
                if (color == PieceColor::White) {
                    list = board->getWhitePieces()->getPieces();
                } else {
                    list = board->getBlackPieces()->getPieces();
                }

                // loop through each piece and each move per piece to create a vector of all valid moves
                std::vector<Move*> moves;
                for (auto piece : *list) {
                    for (auto move : piece->getValidMoves()) {
                        moves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                }

                // use the rand() function to choose a random move in the moves vector
                int num = rand() % moves.size();
                return moves.at(num);
            }
        case 2:
            {
                // gather a list of all pieces of the correct colour
                std::vector<Piece*> * list;
                if (color == PieceColor::White) {
                    list = board->getWhitePieces()->getPieces();
                } else {
                    list = board->getBlackPieces()->getPieces();
                }

                std::vector<Move*> moves;
                std::vector<Move*> captureCheckMoves;

                // loop through each piece
                for (auto piece : *list) {
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    std::vector<Square*> capturemoves = piece->getCapturingMoves();
                    std::vector<Square*> checkmoves = piece->getDeliverChecks();

                    // loop through the valid moves for the given piece and add them to the moves list
                    for (auto move : validmoves) {
                        moves.push_back(new Move(piece->getPosition(), move, piece));
                    }

                    // loop through the capturing moves for the given piece and add them to the captures and checks list
                    for (auto move : capturemoves) {
                        captureCheckMoves.push_back(new Move(piece->getPosition(), move, piece));
                    }

                    // loop through the moves that deliver check for the given piece and add them to the captures and checks list
                    for (auto move : checkmoves) {
                        captureCheckMoves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                }

                // if there are any moves that capture or deliver check
                if (captureCheckMoves.size() != 0) {
                    // randomly pick one of those moves
                    int num = rand() % captureCheckMoves.size();
                    return captureCheckMoves.at(num);
                } else {
                    // otherwise randomly pick a valid move
                    int num = rand() % moves.size();
                    return moves.at(num);
                }
            }
        case 3:
            {
                // gather a list of all pieces of the correct colour
                std::vector<Piece*> * list;
                if (color == PieceColor::White) {
                    list = board->getWhitePieces()->getPieces();
                } else {
                    list = board->getBlackPieces()->getPieces();
                }

                std::vector<Move*> moves;
                std::vector<Move*> preferredMoves;

                // loop through each piece
                for (auto piece : *list) {

                    // loop through the given piece's valid moves and add them to the moves vector
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    for (auto move : validmoves) {
                        moves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                    validmoves.clear();

                    // loop through the given piece's capturing moves and add them to the preferredMoves vector
                    std::vector<Square*> capturemoves = piece->getCapturingMoves();
                    for (auto move : capturemoves) {
                        preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                    }

                    // loop through the given piece's moves that deliver check and add them to the preferredMoves vector
                    std::vector<Square*> checkmoves = piece->getDeliverChecks();
                    for (auto move : checkmoves) {
                        preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                }

                // create a list of the opposite colour's pieces
                std::vector<Piece*> * newlist;
                std::vector<Square*> otherColorMoves;
                if (color == PieceColor::Black) {
                    newlist = board->getWhitePieces()->getPieces();
                } else {
                    newlist = board->getBlackPieces()->getPieces();
                }

                // loop through the opponent's pieces
                for (auto piece : *newlist) {
                    std::vector<Square*> othermoves;

                    // if their piece is a pawn get their moves that can take a piece otherwise get valid moves
                    if (piece->getPieceType() == PieceType::WhitePawn || piece->getPieceType() == PieceType::BlackPawn) {
                        othermoves = piece->getMovesToCapture();
                    } else {
                        othermoves = piece->getValidMoves();
                    }
                    
                    // add each move to the otherColorMoves vector
                    for (auto move : othermoves) {
                        otherColorMoves.push_back(move);
                    }
                }

                // loop through each piece
                for (auto piece : *list) {
                    // if it cannot be capture continue to next iteration of the loop
                    if (!piece->canBeCaptured()) continue;
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    // loop through each piece's valid moves
                    for (auto move : validmoves) {
                        bool safe = true;
                        // loop through the opponent's valid moves
                        for (auto otherMove : otherColorMoves) {
                            if (move == otherMove) {
                                safe = false;
                            }
                        }
                        // if the given move cannot be taken add to preferredMoves vector
                        if (safe) {
                            preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                        }
                    }
                }

                // if there are any preferredMoves
                if (preferredMoves.size() != 0) {
                    // randomly pick
                    int num = rand() % preferredMoves.size();
                    return preferredMoves.at(num);
                } else {
                    // otherwise randomly pick validmove
                    int num = rand() % moves.size();
                    return moves.at(num);
                }
                break;
            }
        case 4:
            {
                // if this is the first move
                if (moveCount == 0) {
                    // randomly pick an opening
                    opening = (rand() % 3) + (int) color * 3;
                }

                // gather a list of all the pieces of the correct colour
                std::vector<Piece*> * list;
                if (color == PieceColor::White) {
                    list = board->getWhitePieces()->getPieces();
                } else {
                    list = board->getBlackPieces()->getPieces();
                }
                
                // gather a list of all valid moves of the valid colour
                std::vector<Move*> moves;
                for (auto piece : *list) {
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    for (auto move : validmoves) {
                        moves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                }

                // return the opening move if it is within the first 5 moves and the move is valid
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

                // loop through each piece
                for (auto piece : *list) {
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    // test each move to see if it is an attack or fork
                    for (auto move : validmoves) {
                        int fromRow = piece->getPosition()->getRow();
                        int fromCol = piece->getPosition()->getCol();
                        int toRow = move->getRow();
                        int toCol = move->getCol();
                        board->getCell(fromRow, fromCol)->setPiece(nullptr);
                        Piece *old = board->getCell(toRow, toCol)->getPiece();
                        board->getCell(toRow, toCol)->setPiece(piece);
                        piece->setPosition(toRow, toCol);
                        // if there is a fork or attack add move to forks or attacks vectors
                        if (piece->getCapturingMoves().size() > 1) {
                            forks.push_back(new Move(board->getCell(fromRow, fromCol), move, piece));
                        } else if (piece->getCapturingMoves().size() > 0) {
                            attacks.push_back(new Move(board->getCell(fromRow, fromCol), move, piece));
                        }
                        board->getCell(fromRow, fromCol)->setPiece(piece);
                        board->getCell(toRow, toCol)->setPiece(old);
                        piece->setPosition(fromRow, fromCol);
                    }

                    // loop through capturing moves and add them to preferredMoves
                    validmoves = piece->getCapturingMoves();
                    for (auto move : validmoves) {
                        preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                    }

                    // loop through moves that deliver check and add them to preferredMoves
                    validmoves = piece->getDeliverChecks();
                    for (auto move : validmoves) {
                        preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                    }
                }

                // gather a list of the opponent's pieces
                std::vector<Piece*> * newlist;
                std::vector<Square*> otherColorMoves;
                if (color == PieceColor::Black) {
                    newlist = board->getWhitePieces()->getPieces();
                } else {
                    newlist = board->getBlackPieces()->getPieces();
                }

                // loop through the opponent's pieces
                for (auto piece : *newlist) {
                    std::vector<Square*> othermoves;
                    // if piece is a pawn return moves that can capture otherwise return valid moves
                    if (piece->getPieceType() == PieceType::WhitePawn || piece->getPieceType() == PieceType::BlackPawn) {
                        othermoves = piece->getMovesToCapture();
                    } else {
                        othermoves = piece->getValidMoves();
                    }
                    // gather all moves in otherColorMoves vector
                    for (auto move : othermoves) {
                        otherColorMoves.push_back(move);
                    }
                }

                // loop through pieces
                for (auto piece : *list) {
                    bool safe = true;
                    // if it cannot be taken continue to next loop iteration
                    if (!piece->canBeCaptured()) continue;
                    std::vector<Square*> validmoves = piece->getValidMoves();
                    for (auto move : validmoves) {
                        bool safe = true;
                        for (auto otherMove : otherColorMoves) {
                            if (move == otherMove) {
                                safe = false;
                            }
                        }
                        // if the given move cannot be taken add it to preferredMoves vector
                        if (safe) {
                            preferredMoves.push_back(new Move(piece->getPosition(), move, piece));
                        }
                    }
                }
                
                // if there is a preferredMove pick randomly, otherwise if there is a fork, otherwise if there is an attack, otherwise choose randomly
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

// mutator for moveCount
void ComputerEngine::setMoveCount(int count) {
    moveCount = count;
}

// returns opening move
Move* ComputerEngine::playOpening(Board* board) {
    // for each opening and move number return correct move
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