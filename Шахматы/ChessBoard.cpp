#include "Figures.h"
#include <iostream>


ChessBoard::ChessBoard()
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			board[i][j] = nullptr;

	for (int i = 0; i < 8; ++i)
	{
		board[i][1] = new Pawn(i, 1, true, this);
		board[i][6] = new Pawn(i, 6, false, this);
	}

	board[0][0] = new Castle(0, 0, true, this);
	board[7][0] = new Castle(7, 0, true, this);
	board[0][7] = new Castle(0, 7, false, this);
	board[7][7] = new Castle(7, 7, false, this);

	board[1][0] = new Knight(1, 0, true, this);
	board[6][0] = new Knight(6, 0, true, this);
	board[1][7] = new Knight(1, 7, false, this);
	board[6][7] = new Knight(6, 7, false, this);

	board[2][0] = new Bishop(2, 0, true, this);
	board[5][0] = new Bishop(5, 0, true, this);
	board[2][7] = new Bishop(2, 7, false, this);
	board[5][7] = new Bishop(5, 7, false, this);

	board[3][0] = new Queen(3, 0, true, this);
	board[3][7] = new Queen(3, 7, false, this);

	board[4][0] = new King(4, 0, true, this);
	board[4][7] = new King(4, 7, false, this);
}


ChessBoard::~ChessBoard()
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			delete board[i][j];
}

void ChessBoard::show()
{
	for (int i = 7; i >= 0; i--)
	{
		cout << "   =================================================" << endl;
		//			<< "|       |       |       |       |       |       |       |       |" << endl;
		cout << i + 1 << "  ";
		for (int j = 0; j < 8; j++)
		{
			if (board[j][i] == nullptr)
				cout << "|     ";
			else
				cout << "| " << board[j][i]->getName() << " ";
		}
		cout << "|" << endl;
		//			<< "|       |       |       |       |       |       |       |       |" << endl;
	}
	cout << "   =================================================" << endl
		<< "      1     2     3     4     5     6     7     8" << endl;
}

Figures ** ChessBoard::operator[](int _index)
{
	return board[_index];
}
