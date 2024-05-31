#ifndef UNIQUE_BOARD
#define UNIQUE_BOARD

#include <iostream>
#include <string>
#include <vector>

#include "piece.h"

class Board {
    public:
        Board();

        ~Board();

        int colorTurn();

        std::vector<std::string> boardMoves(std::vector<std::string>* activePieces, int color); // can return null pointer to detect checkmate or stalemate

        void move(Piece piece, int toRank, int toFile); // update active pieces after the move is done

        void updateBoard();

    private:
        Piece board[8][8];
        std::vector<std::string> validMoves;
        std::vector<std::string> activePieces;
        int playerTurn;
};

#endif // UNIQUE_BOARD