#include "Figures.h"
#include "ChessBoard.h"
#include <iostream>

#define PRIORITY_PAWN 1
#define PRIORITY_CASTLE 2
#define PRIORITY_BISHOP 2
#define PRIORITY_KNIGHT 3
#define PRIORITY_QUEEN 10
#define PRIORITY_KING 20


ChessBoard::ChessBoard()
{
	board = new Figures**[8];

	playerColor = true;

	for (int i = 0; i < 8; ++i)
	{
		board[i] = new Figures*[8];
		for (int j = 0; j < 8; ++j)
			board[i][j] = nullptr;
	}
	
	for (int i = 0; i < 8; ++i)
	{
		board[i][1] = new Pawn(i, 1, PRIORITY_PAWN, true, *this, turnsCounter);
		board[i][6] = new Pawn(i, 6, PRIORITY_PAWN, false, *this, turnsCounter);
	}
	{
		board[0][0] = new Castle(0, 0, PRIORITY_CASTLE, true, *this, turnsCounter);
		board[7][0] = new Castle(7, 0, PRIORITY_CASTLE, true, *this, turnsCounter);
		board[0][7] = new Castle(0, 7, PRIORITY_CASTLE, false, *this, turnsCounter);
		board[7][7] = new Castle(7, 7, PRIORITY_CASTLE, false, *this, turnsCounter);

		board[1][0] = new Knight(1, 0, PRIORITY_KNIGHT, true, *this, turnsCounter);
		board[6][0] = new Knight(6, 0, PRIORITY_KNIGHT, true, *this, turnsCounter);
		board[1][7] = new Knight(1, 7, PRIORITY_KNIGHT, false, *this, turnsCounter);
		board[6][7] = new Knight(6, 7, PRIORITY_KNIGHT, false, *this, turnsCounter);

		board[2][0] = new Bishop(2, 0, PRIORITY_BISHOP, true, *this, turnsCounter);
		board[5][0] = new Bishop(5, 0, PRIORITY_BISHOP, true, *this, turnsCounter);
		board[2][7] = new Bishop(2, 7, PRIORITY_BISHOP, false, *this, turnsCounter);
		board[5][7] = new Bishop(5, 7, PRIORITY_BISHOP, false, *this, turnsCounter);

		board[3][0] = new Queen(3, 0, PRIORITY_QUEEN, true, *this, turnsCounter);
		board[3][7] = new Queen(3, 7, PRIORITY_QUEEN, false, *this, turnsCounter);

		board[4][0] = new King(4, 0, PRIORITY_KING, true, *this, turnsCounter);
		board[4][7] = new King(4, 7, PRIORITY_KING, false, *this, turnsCounter);
	}

	whiteKing = board[4][0];
	blackKing = board[4][7];

	for (int i = 0; i < 8; ++i)
	{
		figures.push_back(board[i][0]);
		figures.push_back(board[i][1]);
		figures.push_back(board[i][6]);
		figures.push_back(board[i][7]);
	}
}

ChessBoard::ChessBoard(const ChessBoard& _other)
{
	board = new Figures * *[8];
	playerColor = _other.playerColor;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; i < 8; ++j)
		{

		}
	}
}

ChessBoard::~ChessBoard()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
			delete board[i][j];
		delete[] board[i];
	}
	delete[] board;
}

void ChessBoard::show() const
{
	cout << "Turn number: " << turnsCounter.getCount() + 1 << endl;
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

const vector<Figures*>& ChessBoard::getFigures() const
{
	return figures;
}

Figures** ChessBoard::operator[](int _index)
{
	return board[_index];
}
