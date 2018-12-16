#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Figures.h"

class ChessBoard
{
public:
	ChessBoard();
	~ChessBoard();
	Figures* board[8][8];
};



#endif // !CHESSBOARD_H