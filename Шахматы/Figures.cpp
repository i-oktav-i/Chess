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
	/*
		pos.first = _x;
		pos.second = _y;
	*/
	color = _color;
	priority = _priority;
}

bool Figures::move(int _x, int _y)
{
	if (checkMove(_x, _y))
	{
		setPos(_x, _y);
		++turnsCounter;
		turnOfLastMove = turnsCounter.getCount();
		++movesCounter;
		return true;
	}
	return false;
}

vector<pair<int, int> >& Figures::getPosibleMoves() const
{
	vector<pair<int, int> > moves;
	for (int x = 0; x < 8; ++x)
		for (int y = 0; y < 8; ++y)
			if (checkMove(x, y))
				moves.push_back(pair<int, int>(x, y));
}

vector<pair<int, int>>& Figures::getEatPieceMoves() const
{
	vector<pair<int, int>> moves;
	for (auto i : getPosibleMoves())
	{
		if (board[i.first][i.second] != nullptr)
			moves.push_back(i);
	}
	return moves;
}

bool Figures::isInDanger()
{
	for (int x = 0; x < 8; ++x)
		for (int y = 0; y < 8; ++y)
			if (board[x][y] != nullptr && board[x][y]->checkMove(xPos, yPos))
				return true;
	return false;
}

bool Figures::isInDanger(int _x, int _y)
{
	for (int x = 0; x < 8; ++x)
		for (int y = 0; y < 8; ++y)
			if (board[x][y] != nullptr && board[x][y]->checkMove(_x, _y))
				return true;
	return false;
}

inline void Figures::setPos(int _x, int _y)
{
	board[_x][_y] = board[xPos][yPos];
	board[xPos][yPos] = nullptr;
	xPos = _x;
	yPos = _y;
	isMoved = true;
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
			reborn();
		
		if (color && yPos == 5 && board[xPos][4]->getName() == "B_P" && board[xPos][4]->getMovesCounter() == 1)
			board[xPos][4] = nullptr;

		if (!color && yPos == 2 && board[xPos][3]->getName() == "W_P" && board[xPos][3]->getMovesCounter() == 1)
			board[xPos][3] = nullptr;
		
		return true;
	}
	return false;
}

bool Pawn::checkMove(int _x, int _y) const
{
	if (_x >= 8 || _x < 0 || _y >= 8 || _y < 0)
		return false;

	if (board[_x][_y] == nullptr || board[_x][_y]->getColor() != color)
	{
		if (_x == xPos)
		{
			if ((color && (_y - yPos) == 1) || (!color && (yPos - _y) == 1) ||
				(!isMoved && (color && (_y - yPos) == 2) || (!color && (yPos - _y) == 2)))
				return true;
		}
		if ((_x - xPos == 1 || xPos - _x == 1) && 
			(color && (_y - yPos) == 1) || (!color && (yPos - _y) == 1))
		{
			if (board[_x][_y] == nullptr)
			{
				if (((color && yPos == 4 && board[_x][yPos]->getName() == "B_P") ||
					(!color && yPos == 3 && board[_x][yPos]->getName() == "W_P")) &&
					board[_x][yPos]->getTurnOfLastMove() == turnsCounter.getCount() &&
					board[_x][yPos]->getMovesCounter() == 1)
					return true;
			}
			else if(board[_x][_y]->getColor() != color)
					return true;
		}
	}
	return false;
}

vector<pair<int, int>> & Pawn::getPosibleMoves() const
{
	vector<pair<int, int>> moves;
	for (int i = 0; i < 3; ++i)
	{
		if (color && checkMove(xPos - 1 + i, yPos + 1))
			moves.push_back(pair<int, int>(xPos - 1 + i, yPos + 1));
		else if ((!color) && checkMove(xPos - 1 + i, yPos - 1))
			moves.push_back(pair<int, int>(xPos - 1 + i, yPos + 1));
	}
	if (!isMoved)
	{
		if (color && checkMove(xPos, yPos + 2))
			moves.push_back(pair<int, int>(xPos, yPos + 2));
		else if ((!color) && checkMove(xPos, yPos - 2))
			moves.push_back(pair<int, int>(xPos, yPos + 2));
	}
	return moves;
}

void Pawn::reborn()
{
	cout << "Chose figure type:" << endl;
	cout
		<< "1. Queen" << endl
		<< "2. Knight" << endl
		<< "3. Bishop" << endl
		<< "4. Castle" << endl;
	int i;
	while (!(cin >> i) && i >= 0 && i < 5)
	{
		cin.clear();
		while (cin.get() != '\n');
	}
	switch (i)
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

Knight::Knight(int _x, int _y, int _priority, bool _color, ChessBoard& _board, TurnsCounter& _turnsCounter) : Figures(_x, _y, _priority, _color, _board, _turnsCounter)
{
	if (_color)
		name = "W_H";
	else
		name = "B_H";
}

/*bool Knight::move(int _x, int _y)
{
	if (Figures::move(_x, _y))
		return true;
	return false;
}*/

bool Knight::checkMove(int _x, int _y) const
{
	if (_x >= 8 || _x < 0 || _y >= 8 || _y < 0)
		return false;

	if ((abs(_x - xPos == 2) && abs(_y - yPos == 1) ||
		abs(_y - yPos == 2) && abs(_x - xPos == 1))
		&& (board[_x][_y] == nullptr || board[_x][_y]->getColor() != color))
		return true;

	return false;
}

vector<pair<int, int>> & Knight::getPosibleMoves() const
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

/*bool Bishop::move(int _x, int _y)
{
	if (Figures::move(_x, _y))
		return true;
	return false;
}*/

bool Bishop::checkMove(int _x, int _y) const
{
	if (_x >= 8 || _x < 0 || _y >= 8 || _y < 0)
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

vector<pair<int, int>>& Bishop::getPosibleMoves() const
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

bool Castle::move(int _x, int _y)
{
	if (checkMove(_x, _y))
	{
		setPos(_x, _y);
		return true;
	}

	return false;
}

bool Castle::checkMove(int _x, int _y) const
{
	if (_x >= 8 || _x < 0 || _y >= 8 || _y < 0)
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

vector<pair<int, int>>& Castle::getPosibleMoves() const
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

bool Queen::move(int _x, int _y)
{
	if (checkMove(_x, _y))
	{
		setPos(_x, _y);
		return true;
	}
	return false;
}

bool Queen::checkMove(int _x, int _y) const
{
	if (_x >= 8 || _x < 0 || _y >= 8 || _y < 0)
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

vector<pair<int, int>>& Queen::getPosibleMoves() const
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
	if (checkMove(_x, _y))
	{
		setPos(_x, _y);
		return true;
	}

	return false;
}

bool King::checkMove(int _x, int _y) const
{
	if (_x >= 8 || _x < 0 || _y >= 8 || _y < 0)
		return false;

	if (
		abs(_x - xPos) <= 1 && abs(_y - yPos) <= 1 && (
			board[_x][_y] == nullptr || board[_x][_y]->getColor() != color &&
			!this->isCheck(_x, _y)
			)
		)
		return true;

	return false;
}

vector<pair<int, int>>& King::getPosibleMoves() const
{
	vector<pair<int, int>> moves;	

	if (checkMove(xPos + 1, yPos + 1))
		moves.push_back(pair<int, int>(xPos + 1, yPos + 1));
	
	if (checkMove(xPos + 1, yPos))
		moves.push_back(pair<int, int>(xPos + 1, yPos));
	
	if (checkMove(xPos + 1, yPos - 1))
		moves.push_back(pair<int, int>(xPos + 1, yPos - 1));
	
	if (checkMove(xPos, yPos - 1))
		moves.push_back(pair<int, int>(xPos, yPos - 1));
	
	if (checkMove(xPos - 1, yPos - 1))
		moves.push_back(pair<int, int>(xPos - 1, yPos - 1));
	
	if (checkMove(xPos - 1, yPos))
		moves.push_back(pair<int, int>(xPos - 1, yPos));
	
	if (checkMove(xPos - 1, yPos + 1))
		moves.push_back(pair<int, int>(xPos - 1, yPos + 1));
	
	if (checkMove(xPos, yPos + 1))
		moves.push_back(pair<int, int>(xPos, yPos + 1));

	return moves;
}

bool King::isCheck(int _x, int _y) const
{
	for (auto i : board.getFigures())
	{
		if (i->getColor() != color && !i->getIsDead() && i->checkMove(_x, _y))
			return true;
	}

	return false;
}

bool King::isCheckmate()
{
	auto moves = getPosibleMoves();

	if (isCheck(xPos, yPos))
	{
		for (auto i : moves)
		{
			if (!isCheck(i.first, i.second))
				return false;
		}
	}
	
	return false;
}
