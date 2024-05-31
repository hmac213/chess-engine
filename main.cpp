#include <SDL2/SDL.h>
#include "board.h"

#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 800

Board::Board() {
    // initialize all files and ranks

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j].file = j;
            board[i][j].rank = i;
        }
    }

    // initialize empty squares
    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j].color = -1;
            board[i][j].name = "e";
        }
    }

    // initialize white pawns

    for (int i = 0; i < 8; ++i) {
        board[1][i].color = 0;
        board[1][i].name = "p";
    }

    // initialize black pawns

    for (int i = 0; i < 8; ++i) {
        board[6][i].color = 1;
        board[6][i].name = "p";
    }

    // initialize white pieces

    for (int i = 0; i < 8; ++i) {
        board[0][i].color = 0;
    }
    
    board[0][0].name = "r";
    board[0][7].name = "r";
    board[0][1].name = "b";
    board[0][6].name = "b";
    board[0][2].name = "n";
    board[0][5].name = "n";
    board[0][3].name = "q";
    board[0][4].name = "k";

    // initialize black pieces

    for (int i = 0; i < 8; ++i) {
        board[7][i].color = 1;
    }

    board[7][0].name = "r";
    board[7][7].name = "r";
    board[7][1].name = "b";
    board[7][6].name = "b";
    board[7][2].name = "n";
    board[7][5].name = "n";
    board[7][3].name = "q";
    board[7][4].name = "k";
}

std::vector<std::string> Board::boardMoves(std::vector<std::string>* activePieces, int color) {

    /*
    
    Moves are going to be implemented with strings:

    First two characters, PIECE COLOR (1) + PIECE NAME (1)
    Next two characters, RANK FROM (1) + FILE FROM (1)
    Next two characters, RANK TO (1) + FILE TO (1)
    Last Character, Is it a take -> 0 no, 1 yes ----> STILL NEED TO SEE IF NEEDED

    OVERALL: 7 Characters

    example would be: 0p10211 -> white pawn goes from (1,0) to (2,1), while taking

    */

    for (const auto& rank : board) {
        for (const auto& piece : rank) {
            int curRank = piece.rank;
            int curFile = piece.file;

            if (piece.name == "e") {
                return ;
            }

            /*
            Implementation of searching for valid pawn moves. Things to include:
            - Has not moved -> 1 or 2 space advance, diagonal take
            - Has moved -> 1 space advance, diagonal take
            - Special cases:
                - Promotion: How do we do piece conversion (default: Queen)
                - En Passant: Skip-take on a pawn that has jumped two from default square
            */

            if (piece.name == "p") {
                // double jumps for unmoved pawns

                if (piece.hasMoved == false) {
                    if (color == 0) {
                        if (board[curRank + 1][curFile].name == "e" && board[curRank + 2][curFile].name == "e") {
                            validMoves.push_back(std::to_string(piece.color) + 'p' + std::to_string(curRank) + std::to_string(curFile) + std::to_string(curRank + 2) + std::to_string(curFile) + '0');
                        }
                    } else {
                        if (board[curRank - 1][curFile].name == "e" && board[curRank - 2][curFile].name == "e") {
                            validMoves.push_back(std::to_string(piece.color) + 'p' + std::to_string(curRank) + std::to_string(curFile) + std::to_string(curRank - 2) + std::to_string(curFile) + '0');
                        }
                    }
                }

                // single jumps for any pawn

                if (color == 0) {
                    if (curRank < 7) {
                        if (board[curRank + 1][curFile].name == "e") {
                            validMoves.push_back(std::to_string(piece.color) + 'p' + std::to_string(curRank) + std::to_string(curFile) + std::to_string(curRank + 1) + std::to_string(curFile) + '0');
                        }
                    }
                } else {
                    if (curRank > 0) {
                        if (board[curRank - 1][curFile].name == "e") {
                            validMoves.push_back(std::to_string(piece.color) + 'p' + std::to_string(curRank) + std::to_string(curFile) + std::to_string(curRank - 1) + std::to_string(curFile) + '0');
                        }
                    }
                }

                // takes for any pawn

                if (color == 0) {
                    if (curFile > 0) {
                        if (board[curRank + 1][curFile - 1].color == 1) {
                            validMoves.push_back(std::to_string(piece.color) + 'p' + std::to_string(curRank) + std::to_string(curFile) + std::to_string(curRank + 1) + std::to_string(curFile - 1) + '1');
                        }
                    }

                    if (curFile < 7) {
                        if (board[curRank + 1][curFile + 1].color == 1) {
                            validMoves.push_back(std::to_string(piece.color) + 'p' + std::to_string(curRank) + std::to_string(curFile) + std::to_string(curRank + 1) + std::to_string(curFile + 1) + '0');
                        }
                    }
                } else {
                    if (curFile > 0) {
                        if (board[curRank - 1][curFile - 1].color == 0) {
                            validMoves.push_back(std::to_string(piece.color) + 'p' + std::to_string(curRank) + std::to_string(curFile) + std::to_string(curRank - 1) + std::to_string(curFile - 1) + '1');
                        }
                    }

                    if (curFile < 7) {
                        if (board[curRank - 1][curFile + 1].color == 0) {
                            validMoves.push_back(std::to_string(piece.color) + 'p' + std::to_string(curRank) + std::to_string(curFile) + std::to_string(curRank - 1) + std::to_string(curFile + 1) + '0');
                        }
                    }
                }

                // en passant for valid pawns

                if (color == 0) {
                    if (curFile > 0) {
                        if (curRank == 4 && board[curRank][curFile - 1].name == "p" && board[curRank][curFile - 1].color == 1 && board[curRank][curFile - 1].pawnDoubleJump == true) {
                            validMoves.push_back(std::to_string(piece.color) + 'p' + std::to_string(curRank) + std::to_string(curFile) + std::to_string(curRank + 1) + std::to_string(curFile - 1) + '1');
                        }
                    }

                    if (curFile < 7) {
                        if (curRank == 4 && board[curRank][curFile + 1].name == "p" && board[curRank][curFile + 1].color == 1 && board[curRank][curFile + 1].pawnDoubleJump == true) {
                            validMoves.push_back(std::to_string(piece.color) + 'p' + std::to_string(curRank) + std::to_string(curFile) + std::to_string(curRank + 1) + std::to_string(curFile + 1) + '1');
                        }
                    }
                } else {
                    if (curFile > 0) {
                        if (curRank == 3 && board[curRank][curFile - 1].name == "p" && board[curRank][curFile - 1].color == 1 && board[curRank][curFile - 1].pawnDoubleJump == true) {
                            validMoves.push_back(std::to_string(piece.color) + 'p' + std::to_string(curRank) + std::to_string(curFile) + std::to_string(curRank - 1) + std::to_string(curFile - 1) + '1');
                        }
                    }

                    if (curFile < 7) {
                        if (curRank == 3 && board[curRank][curFile + 1].name == "p" && board[curRank][curFile + 1].color == 1 && board[curRank][curFile + 1].pawnDoubleJump == true) {
                            validMoves.push_back(std::to_string(piece.color) + 'p' + std::to_string(curRank) + std::to_string(curFile) + std::to_string(curRank - 1) + std::to_string(curFile + 1) + '1');
                        }
                    }
                }

                // promotion for valid pawns ---> DONT WRITE YET, SHOULD IMPLEMENT IN MOVE() FUNCTION INSTEAD

                if (color == 0) {

                } else {
                    
                }
            }

            if (piece.name == "n") {

            }

            if (piece.name == "b") {

            }

            if (piece.name == "r") {

            }

            if (piece.name == "q") {

            }

            if (piece.name == "k") {

            }
        }
    }

    return validMoves;
}

// void Board::updateBoard() {

// }

int main(int argc, char* argv[]) {
    return 0;
}
 