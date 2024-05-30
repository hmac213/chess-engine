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
            board[i][j].name = "000";
        }
    }

    // initialize white pawns

    for (int i = 0; i < 8; ++i) {
        board[1][i].color = 0;
        board[1][i].name = "001";
    }

    // initialize black pawns

    for (int i = 0; i < 8; ++i) {
        board[6][i].color = 1;
        board[6][i].name = "001";
    }

    // initialize white pieces

    for (int i = 0; i < 8; ++i) {
        board[0][i].color = 0;
    }
    
    board[0][0].name = "100";
    board[0][7].name = "100";
    board[0][1].name = "011";
    board[0][6].name = "011";
    board[0][2].name = "010";
    board[0][5].name = "010";
    board[0][3].name = "101";
    board[0][4].name = "110";

    // initialize black pieces

    for (int i = 0; i < 8; ++i) {
        board[7][i].color = 1;
    }

    board[7][0].name = "100";
    board[7][7].name = "100";
    board[7][1].name = "011";
    board[7][6].name = "011";
    board[7][2].name = "010";
    board[7][5].name = "010";
    board[7][3].name = "101";
    board[7][4].name = "110";
}

std::vector<std::string>* Board::boardMoves(std::vector<std::string> &activePieces, int color) {

    /*
    
    Moves are going to be implemented with strings:

    First four characters, PIECE COLOR (1) + PIECE NAME (3)
    Next two characters, RANK FROM (1) + FILE FROM (1)
    Next two characters, RANK TO (1) + FILE TO (1)
    Last Character, Is it a take -> 0 no, 1 yes ----> STILL NEED TO SEE IF NEEDED

    OVERALL: 9 Characters

    need to look into whether I should adopt a more efficient naming system (ie. pieces are 1 char)
        p = pawn
        n = knight
        b = bishop
        r = rook
        q = queen
        k = king
    Would only eliminate two characters though.

    */

    std::vector<std::string>* validMoves;
    for (const auto& rank : board) {
        for (const auto& piece : rank) {
            int curRank = piece.rank;
            int curFile = piece.file;
            char rankChar = '0' + curRank;
            char fileChar = '0' + curFile;

            if (piece.name == "000") {
                return nullptr;
            }

            /*
            Implementation of searching for valid pawn moves. Things to include:
            - Has not moved -> 1 or 2 space advance, diagonal take
            - Has moved -> 1 space advance, diagonal take
            - Special cases:
                - Promotion: How do we do piece conversion (default: Queen)
                - En Passant: Skip-take on a pawn that has jumped two from default square
            */

            if (piece.name == "001") {
                if (piece.hasMoved == true) {
                    if (piece.color == 0) {
                        int nextRank = piece.rank + 1;
                        if (nextRank < 7) {
                            if (board[nextRank][curFile].name == "000") {
                                
                            }
                        }
                    } else {
                        int nextRank = piece.rank - 1;
                        if (nextRank > 0) {
                            if (board[nextRank][curFile].name == "000") {

                            }
                        }
                    }
                } else {

                }
            }

            if (piece.name == "010") {

            }

            if (piece.name == "011") {

            }

            if (piece.name == "100") {

            }

            if (piece.name == "101") {

            }

            if (piece.name == "110") {

            }
        }
    }
}

// void Board::updateBoard() {

// }

int main(int argc, char* argv[]) {
    return 0;
}
 