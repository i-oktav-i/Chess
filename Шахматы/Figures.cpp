#include "Figures.h"
#include <math.h>
#include <iostream>

#define PRIORITY_PAWN 1
#define PRIORITY_CASTLE 2
#define PRIORITY_BISHOP 2
#define PRIORITY_KNIGHT 3
#define PRIORITY_QUEEN 10
#define PRIORITY_KING 20

Figures::Figures(int _x, int _y, int _priority, bool _color, ChessBoard& _board, TurnsCounter& _turnsCounter) : board(_board), turnsCounter(_turnsCounter)
{
	xPos = _x;
	yPos = _y;
	color = _color;
	priority = _priority;
}

bool Figures::move(int _x, int _y)
{
	if (checkMove(_x, _y) && !willBeOnCheck(_x, _y))
	{
		setPos(_x, _y);
		turnOfLastMove = ++turnsCounter;
		++movesCounter;
		isMoved = true;
		return true;
	}
	return false;
}

bool Figures::willBeOnCheck(int _x, int _y)
{
	Figures* piece = board[_x][_y];
	int oldX = xPos, oldY = yPos;
	setPos(_x, _y);
	turnOfLastMove = ++turnsCounter;
	++movesCounter;

	bool willBeOnCheck = false;

	if (color)
		willBeOnCheck = board.getWhiteKing()->isInDanger();
	else
		willBeOnCheck = board.getBlackKing()->isInDanger();

	setPos(oldX, oldY);
	turnOfLastMove = --turnsCounter;
	--movesCounter;
	board[_x][_y] = piece;

	return willBeOnCheck;
}
bool Figures::willBeCheckmate(int _x, int _y)
{
	Figures* piece = board[_x][_y];
	int oldX = xPos, oldY = yPos;
	setPos(_x, _y);
	turnOfLastMove = ++turnsCounter;
	++movesCounter;

	bool willBeCheckmate = false;

	if (!color)
		willBeCheckmate = board.getWhiteKing()->havePossibleMoves() && board.getWhiteKing()->isInDanger();
	else
		willBeCheckmate = board.getBlackKing()->havePossibleMoves() && board.getBlackKing()->isInDanger();

	setPos(oldX, oldY);
	turnOfLastMove = --turnsCounter;
	--movesCounter;
	board[_x][_y] = piece;

	return willBeCheckmate;
}

vector<pair<int, int> > Figures::getPosibleMoves() const
{
	vector<pair<int, int> > moves;
	for (int x = 0; x < 8; ++x)
		for (int y = 0; y < 8; ++y)
			if (checkMove(x, y))
				moves.push_back(pair<int, int>(x, y));

	return moves;
}

vector<pair<int, int>> & Figures::getEatPieceMoves() const
{
	vector<pair<int, int>> moves;
	for (auto i : getPosibleMoves())
	{
		if (board[i.first][i.second] != nullptr)
			moves.push_back(i);
	}
	return moves;
}

bool Figures::isInDanger() const
{
	for (int x = 0; x < 8; ++x)
		for (int y = 0; y < 8; ++y)
			if (board[x][y] != nullptr && board[x][y]->checkMove(xPos, yPos))
				return true;
	return false;
}

bool Figures::isInDanger(int _x, int _y) const
{
	for (int x = 0; x < 8; ++x)
		for (int y = 0; y < 8; ++y)
			if (board[x][y] != nullptr && board[x][y]->getColor() != color && board[x][y] != this && board[x][y]->checkMove(_x, _y))
				return true;
	return false;
}

bool Figures::havePossibleMoves()
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			if (board[i][j] != nullptr && board[i][j]->getColor() == color)
				for (int x = 0; x < 8; ++x)
					for (int y = 0; y < 8; ++y)
						if (board[i][j]->checkMove(x, y) && !board[i][j]->willBeOnCheck(x, y))
							return true;
	return false;
}

inline void Figures::setPos(int _x, int _y)
{
	board[_x][_y] = board[xPos][yPos];
	board[xPos][yPos] = nullptr;
	xPos = _x;
	yPos = _y;
}

Pawn::Pawn(int _x, int _y, int _priority, bool _color, ChessBoard & _board, TurnsCounter & _turnsCounter) : Figures(_x, _y, _priority, _color, _board, _turnsCounter)
{
	if (_color)
		name = "W_P";
	else
		name = "B_P";
}

bool Pawn::move(int _x, int _y)
{
	if (Figures::move(_x, _y))
	{
		if (yPos == 7 || yPos == 0)
			yPos;

		if (color && yPos == 5 && board[xPos][4] != nullptr && board[xPos][4]->getName() == "B_P" && board[xPos][4]->getMovesCounter() == 1)
			board[xPos][4] = nullptr;

		if (!color && yPos == 2 && board[xPos][3] != nullptr && board[xPos][3]->getName() == "W_P" && board[xPos][3]->getMovesCounter() == 1)
			board[xPos][3] = nullptr;

		return true;
	}
	return false;
}

bool Pawn::checkMove(int _x, int _y) const 
{
	if ((_x == xPos && _y == yPos) || _x >= 8 || _x < 0 || _y >= 8 || _y < 0)
		return false;


	if (_x == xPos)
	{
		if (color && (_y - yPos) == 1 && board[_x][_y] == nullptr)
			return true;


		if (color && !isMoved && (_y - yPos) == 2 && board[_x][_y - 1] == nullptr && board[_x][_y] == nullptr)
			return true;

		if (!color && (_y - yPos) == -1 && board[_x][_y] == nullptr)
			return true;


		if (!color && !isMoved && (_y - yPos) == -2 && board[_x][_y + 1] == nullptr && board[_x][_y] == nullptr)
			return true;

	}
	if (_x - xPos == 1 || xPos - _x == 1) 
	{
		if (board[_x][_y] != nullptr)
		{
			if (color && (_y - yPos == 1) && board[_x][_y]->getColor() != color)
				return true;
			if (!color && (_y - yPos == -1) && board[_x][_y]->getColor() != color)
				return true;
		}
		else
		{
			if (((color && yPos == 4 && _y == 5 && board[_x][yPos] != nullptr && board[_x][yPos]->getName() == "B_P") ||
				(!color && yPos == 3 && _y == 2 && board[_x][yPos] != nullptr && board[_x][yPos]->getName() == "W_P")) &&
				board[_x][yPos]->getTurnOfLastMove() == turnsCounter.getCount() &&
				board[_x][yPos]->getMovesCounter() == 1)
				return true;
		}
	}
	return false;
}

//vector<pair<int, int>> Pawn::getPosibleMoves() const
//{
//	vector<pair<int, int>> moves;
//	for (int i = 0; i < 3; ++i)
//	{
//		if (color && checkMove(xPos - 1 + i, yPos + 1))
//			moves.push_back(pair<int, int>(xPos - 1 + i, yPos + 1));
//		else if ((!color) && checkMove(xPos - 1 + i, yPos - 1))
//			moves.push_back(pair<int, int>(xPos - 1 + i, yPos + 1));
//	}
//	if (!isMoved)
//	{
//		if (color && checkMove(xPos, yPos + 2))
//			moves.push_back(pair<int, int>(xPos, yPos + 2));
//		else if ((!color) && checkMove(xPos, yPos - 2))
//			moves.push_back(pair<int, int>(xPos, yPos + 2));
//	}
//	return moves;
//}

void Pawn::reborn(int _i)
{
	switch (_i)
	{
	case 1:
		board[xPos][yPos] = new Queen(xPos, yPos, PRIORITY_QUEEN, color, board, turnsCounter);
		break;
	case 2:
		board[xPos][yPos] = new Knight(xPos, yPos, PRIORITY_KNIGHT, color, board, turnsCounter);
		break;
	case 3:
		board[xPos][yPos] = new Bishop(xPos, yPos, PRIORITY_BISHOP, color, board, turnsCounter);
		break;
	case 4:
		board[xPos][yPos] = new Castle(xPos, yPos, PRIORITY_CASTLE, color, board, turnsCounter);
		break;
	default:
		break;
	}
}

Knight::Knight(int _x, int _y, int _priority, bool _color, ChessBoard & _board, TurnsCounter & _turnsCounter) : Figures(_x, _y, _priority, _color, _board, _turnsCounter)
{
	if (_color)
		name = "W_H";
	else
		name = "B_H";
}


bool Knight::checkMove(int _x, int _y) const 
{
	if ((_x == xPos && _y == yPos) || _x >= 8 || _x < 0 || _y >= 8 || _y < 0)
		return false;

	if (abs(_x - xPos) == 2 && abs(_y - yPos) == 1 || abs(_y - yPos) == 2 && abs(_x - xPos) == 1)
		if (board[_x][_y] == nullptr || board[_x][_y]->getColor() != color)
			return true;

	return false;
}

vector<pair<int, int>>  Knight::getPosibleMoves() const
{
	vector<pair<int, int>> moves;

	if (checkMove(xPos + 1, yPos + 2))
		moves.push_back(pair<int, int>(xPos + 1, yPos + 2));

	if (checkMove(xPos + 1, yPos - 2))
		moves.push_back(pair<int, int>(xPos + 1, yPos - 2));

	if (checkMove(xPos - 1, yPos + 2))
		moves.push_back(pair<int, int>(xPos - 1, yPos + 2));

	if (checkMove(xPos - 1, yPos - 2))
		moves.push_back(pair<int, int>(xPos - 1, yPos - 2));

	if (checkMove(xPos + 2, yPos + 1))
		moves.push_back(pair<int, int>(xPos + 2, yPos + 1));

	if (checkMove(xPos + 2, yPos - 1))
		moves.push_back(pair<int, int>(xPos + 2, yPos - 1));

	if (checkMove(xPos - 2, yPos + 1))
		moves.push_back(pair<int, int>(xPos - 2, yPos + 1));

	if (checkMove(xPos - 2, yPos - 1))
		moves.push_back(pair<int, int>(xPos - 2, yPos - 1));

	return moves;
}

Bishop::Bishop(int _x, int _y, int _priority, bool _color, ChessBoard & _board, TurnsCounter & _turnsCounter) : Figures(_x, _y, _priority, _color, _board, _turnsCounter)
{
	if (_color)
		name = "W_B";
	else
		name = "B_B";
}

bool Bishop::checkMove(int _x, int _y) const 
{
	if ((_x == xPos && _y == yPos) || _x >= 8 || _x < 0 || _y >= 8 || _y < 0)
		return false;

	if (abs(_x - xPos) == abs(_y - yPos))
	{

		int dX = abs(_x - xPos) / (_x - xPos);
		int dY = abs(_y - yPos) / (_y - yPos);

		int _xPos = xPos + dX;
		int _yPos = yPos + dY;

		while (_y != _yPos && board[_xPos][_yPos] == nullptr)
		{
			_yPos += dY;
			_xPos += dX;
		}
		if (_y == _yPos && (board[_x][_y] == nullptr || board[_x][_y]->getColor() != color))
			return true;
	}

	return false;
}

vector<pair<int, int>> Bishop::getPosibleMoves() const
{
	vector<pair<int, int>> moves;
	for (int i = 0; i < 8; ++i)
	{
		if (checkMove(xPos + i, yPos + i))
			moves.push_back(pair<int, int>(xPos + i, yPos + i));

		if (checkMove(xPos + i, yPos - i))
			moves.push_back(pair<int, int>(xPos + i, yPos - i));

		if (checkMove(xPos - i, yPos + i))
			moves.push_back(pair<int, int>(xPos - i, yPos + i));

		if (checkMove(xPos - i, yPos - i))
			moves.push_back(pair<int, int>(xPos - i, yPos - i));
	}

	return moves;
}

Castle::Castle(int _x, int _y, int _priority, bool _color, ChessBoard & _board, TurnsCounter & _turnsCounter) : Figures(_x, _y, _priority, _color, _board, _turnsCounter)
{
	if (_color)
		name = "W_C";
	else
		name = "B_C";
}

bool Castle::checkMove(int _x, int _y) const 
{
	if ((_x == xPos && _y == yPos) || _x >= 8 || _x < 0 || _y >= 8 || _y < 0)
		return false;

	if ((abs(_x - xPos) == 0 && abs(_y - yPos) != 0) || (abs(_x - xPos) != 0 && abs(_y - yPos) == 0))
	{
		int dX, dY, _yPos, _xPos;

		if (abs(_x - xPos))
			dX = abs(_x - xPos) / (_x - xPos);
		else
			dX = 0;

		if (abs(_y - yPos))
			dY = abs(_y - yPos) / (_y - yPos);
		else
			dY = 0;

		_yPos = yPos + dY;
		_xPos = xPos + dX;

		while ((_y != _yPos || _x != _xPos) && board[_xPos][_yPos] == nullptr)
		{
			_yPos += dY;
			_xPos += dX;
		}
		if (_y == _yPos && _x == _xPos && (board[_x][_y] == nullptr || board[_x][_y]->getColor() != color))
			return true;
	}

	return false;
}

vector<pair<int, int>> Castle::getPosibleMoves() const
{
	vector<pair<int, int>> moves;
	for (int i = 0; i < 8; ++i)
	{
		if (checkMove(xPos, yPos + i))
			moves.push_back(pair<int, int>(xPos, yPos + i));
		if (checkMove(xPos, yPos - i))
			moves.push_back(pair<int, int>(xPos, yPos - i));
		if (checkMove(xPos + i, yPos))
			moves.push_back(pair<int, int>(xPos + i, yPos));
		if (checkMove(xPos - i, yPos))
			moves.push_back(pair<int, int>(xPos - i, yPos));
	}
	return moves;
}

Queen::Queen(int _x, int _y, int _priority, bool _color, ChessBoard & _board, TurnsCounter & _turnsCounter) : Figures(_x, _y, _priority, _color, _board, _turnsCounter)
{
	if (_color)
		name = "W_Q";
	else
		name = "B_Q";
}

bool Queen::checkMove(int _x, int _y) const 
{
	if ((_x == xPos && _y == yPos) || _x >= 8 || _x < 0 || _y >= 8 || _y < 0)
		return false;

	if ((abs(_x - xPos) == 0 && abs(_y - yPos) != 0) ||
		(abs(_x - xPos) != 0 && abs(_y - yPos) == 0) ||
		abs(_x - xPos) == abs(_y - yPos))
	{
		int dX, dY, _yPos, _xPos;

		if (abs(_x - xPos))
			dX = abs(_x - xPos) / (_x - xPos);
		else
			dX = 0;

		if (abs(_y - yPos))
			dY = abs(_y - yPos) / (_y - yPos);
		else
			dY = 0;

		_yPos = yPos + dY;
		_xPos = xPos + dX;

		while ((_y != _yPos || _x != _xPos) && board[_xPos][_yPos] == nullptr)
		{
			_yPos += dY;
			_xPos += dX;
		}
		if (_y == _yPos && _x == _xPos && (board[_x][_y] == nullptr || board[_x][_y]->getColor() != color))
			return true;
	}

	return false;
}

vector<pair<int, int>> Queen::getPosibleMoves() const
{
	vector<pair<int, int>> moves;
	for (int i = 0; i < 8; ++i)
	{
		if (checkMove(xPos + i, yPos + i))
			moves.push_back(pair<int, int>(xPos + i, yPos + i));

		if (checkMove(xPos + i, yPos - i))
			moves.push_back(pair<int, int>(xPos + i, yPos - i));

		if (checkMove(xPos - i, yPos + i))
			moves.push_back(pair<int, int>(xPos - i, yPos + i));

		if (checkMove(xPos - i, yPos - i))
			moves.push_back(pair<int, int>(xPos - i, yPos - i));

		if (checkMove(xPos, yPos + i))
			moves.push_back(pair<int, int>(xPos, yPos + i));

		if (checkMove(xPos, yPos - i))
			moves.push_back(pair<int, int>(xPos, yPos - i));

		if (checkMove(xPos + i, yPos))
			moves.push_back(pair<int, int>(xPos + i, yPos));

		if (checkMove(xPos - i, yPos))
			moves.push_back(pair<int, int>(xPos - i, yPos));
	}
	return moves;
}

King::King(int _x, int _y, int _priority, bool _color, ChessBoard & _board, TurnsCounter & _turnsCounter) : Figures(_x, _y, _priority, _color, _board, _turnsCounter)
{
	if (_color)
		name = "W_K";
	else
		name = "B_K";
}

bool King::move(int _x, int _y)
{
	if (Figures::move(_x, _y))
	{
		if (xPos == 2 && (yPos == 0 || yPos == 7) && movesCounter == 1)
		{
			board[3][yPos] = board[0][yPos];
			board[0][yPos] = nullptr;
		}
		if (xPos == 6 && (yPos == 0 || yPos == 7) && movesCounter == 1)
		{
			board[5][yPos] = board[7][yPos];
			board[7][yPos] = nullptr;
		}

		return true;
	}

	return false;
}

bool King::checkMove(int _x, int _y) const 
{
	if ((_x == xPos && _y == yPos) || _x >= 8 || _x < 0 || _y >= 8 || _y < 0)
		return false;

	if (abs(_x - xPos) <= 1 && abs(_y - yPos) <= 1 && (board[_x][_y] == nullptr || board[_x][_y]->getColor() != color) && !isInDanger(_x, _y))
		return true;

	if ((_x == 2 && longRoque() || _x == 6 && shortRoque()) && (_y == 0 || _y == 7))
		return true;

	return false;
}

//vector<pair<int, int>> King::getPosibleMoves() const
//{
//	vector<pair<int, int>> moves;
//
//	if (checkMove(xPos + 1, yPos + 1))
//		moves.push_back(pair<int, int>(xPos + 1, yPos + 1));
//
//	if (checkMove(xPos + 1, yPos))
//		moves.push_back(pair<int, int>(xPos + 1, yPos));
//
//	if (checkMove(xPos + 1, yPos - 1))
//		moves.push_back(pair<int, int>(xPos + 1, yPos - 1));
//
//	if (checkMove(xPos, yPos - 1))
//		moves.push_back(pair<int, int>(xPos, yPos - 1));
//
//	if (checkMove(xPos - 1, yPos - 1))
//		moves.push_back(pair<int, int>(xPos - 1, yPos - 1));
//
//	if (checkMove(xPos - 1, yPos))
//		moves.push_back(pair<int, int>(xPos - 1, yPos));
//
//	if (checkMove(xPos - 1, yPos + 1))
//		moves.push_back(pair<int, int>(xPos - 1, yPos + 1));
//
//	if (checkMove(xPos, yPos + 1))
//		moves.push_back(pair<int, int>(xPos, yPos + 1));
//
//	return moves;
//}

bool King::longRoque() const
{
	if (movesCounter)
		return false;

	if (color && board[0][0] != nullptr && board[0][0]->getName() == "W_C" && !board[0][0]->getTurnOfLastMove())
		if (board[1][0] == nullptr && board[2][0] == nullptr && board[3][0] == nullptr && !board[1][0]->isInDanger() && !board[3][0]->isInDanger() && !isInDanger(2, 0))
			return true;
	if (!color && board[0][7] != nullptr && board[0][7]->getName() == "B_C" && !board[0][7]->getTurnOfLastMove())
		if (board[1][7] == nullptr && board[2][7] == nullptr && board[3][7] == nullptr && !board[1][7]->isInDanger() && !board[3][7]->isInDanger() && !isInDanger(2, 7))
			return true;

	return false;
}

bool King::shortRoque() const
{
	if (movesCounter)
		return false;

	if (color && board[7][0] != nullptr && board[7][0]->getName() == "W_C" && !board[7][0]->getTurnOfLastMove())
		if (board[5][0] == nullptr && !board[5][0]->isInDanger() && board[6][0] == nullptr && !isInDanger(6, 0))
			return true;

	if (!color && board[7][7] != nullptr && board[7][7]->getName() == "B_C" && !board[7][7]->getTurnOfLastMove())
		if (board[5][7] == nullptr && !board[5][7]->isInDanger() && board[6][7] == nullptr && !isInDanger(6, 7))
			return true;

	return false;
}

