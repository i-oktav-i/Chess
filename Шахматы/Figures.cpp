#include "Figures.h"
#include <math.h>
#include <iostream>

#define PRIORITY_PAWN 1
#define PRIORITY_CASTLE 2
#define PRIORITY_BISHOP 2
#define PRIORITY_KNIGHT 3
#define PRIORITY_QUEEN 10
#define PRIORITY_KING 20

Figures::Figures(int _x, int _y, int _priority, bool _color, ChessBoard& _board) : board(_board)
{
	xPos = _x;
	yPos = _y;

	//pos.first = _x;
	//pos.second = _y;

	color = _color;
	priority = _priority;
}

vector<pair<int, int>>& Figures::getEatFigureMoves()
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
	for (auto i : board.getFigures())
	{
		if (i->checkMove(xPos, yPos))
			return true;
	}
	return false;
}

bool Figures::isInDanger(int _x, int _y)
{

	for (auto i : board.getFigures())
	{
		if (i->getColor() != color && i->checkMove(_x, _y))
			return true;
	}

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

Pawn::Pawn(int _x, int _y, bool _color, ChessBoard & _board) : Figures(_x, _y, PRIORITY_PAWN, _color, _board)
{
	if (_color)
		name = "W_P";
	else
		name = "B_P";
}

bool Pawn::move(int _x, int _y)
{
	if (checkMove(_x, _y))
	{
		setPos(_x, _y);

		if ((yPos == 7 && color) || (yPos == 0 && !color))
			reborn();

		return true;
	}

	return false;
}

bool Pawn::checkMove(int _x, int _y) const
{
	if (_x >= 8 || _x < 0 || _y >= 8 || _y < 0)
		return false;

	if (xPos - _x == 0)
	{
		if ((color && (_y - yPos) == 1 && (board[_x][_y] == nullptr || !board[_x][_y]->getColor()))
			|| (color && (_y - yPos) == 2 && !isMoved && (board[_x][_y] == nullptr || !board[_x][_y]->getColor()))
			|| (!color && (_y - yPos) == -1 && (board[_x][_y] == nullptr || board[_x][_y]->getColor()))
			|| (!color && (_y - yPos) == -2 && !isMoved && (board[_x][_y] == nullptr || board[_x][_y]->getColor())))
			return true;

		return false;
	}
	else if (
		(
			_x - xPos == 1 && (
			(color && _y - yPos == 1) ||
				(!color && _y - yPos == -1)
				)
			)
		&& (
			_x - xPos == -1 && (
			(color && _y - yPos == 1) ||
				(!color && _y - yPos == -1)
				)
			)
		)
		return true;

	return false;
}

vector<pair<int, int>>& Pawn::getPosibleMoves()
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
		<< "4. Castle" << endl
		<< "0. Pawn" << endl;
	int i;
	while (!(cin >> i) && i >= 0 && i < 5)
	{
		cin.clear();
		while (cin.get() != '\n');
	}
	switch (i)
	{
	case 1:
		board[xPos][yPos] = new Queen(xPos, yPos, color, board);
		break;
	case 2:
		board[xPos][yPos] = new Knight(xPos, yPos, color, board);
		break;
	case 3:
		board[xPos][yPos] = new Bishop(xPos, yPos, color, board);
		break;
	case 4:
		board[xPos][yPos] = new Castle(xPos, yPos, color, board);
		break;
	case 0:
	default:
		break;
	}
}

Knight::Knight(int _x, int _y, bool _color, ChessBoard & _board) : Figures(_x, _y, PRIORITY_KNIGHT, _color, _board)
{
	if (_color)
		name = "W_H";
	else
		name = "B_H";
}

bool Knight::move(int _x, int _y)
{
	if (checkMove(_x, _y))
	{
		setPos(_x, _y);
		return true;
	}

	return false;
}

bool Knight::checkMove(int _x, int _y) const
{
	if (_x >= 8 || _x < 0 || _y >= 8 || _y < 0)
		return false;

	if (
		(
			abs(_x - xPos) == 2 &&
			abs(_y - yPos) == 1 && (
				board[_x][_y] == nullptr ||
				board[_x][_y]->getColor() != color
				)
			)
		|| (
			abs(_x - xPos) == 1 &&
			abs(_y - yPos) == 2 && (
				board[_x][_y] == nullptr ||
				board[_x][_y]->getColor() != color
				)
			)
		)
		return true;

	return false;
}

vector<pair<int, int>>& Knight::getPosibleMoves()
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

Bishop::Bishop(int _x, int _y, bool _color, ChessBoard& _board) : Figures(_x, _y, PRIORITY_BISHOP, _color, _board)
{
	if (_color)
		name = "W_B";
	else
		name = "B_B";
}

bool Bishop::move(int _x, int _y)
{
	if (checkMove(_x, _y))
	{
		setPos(_x, _y);
		return true;
	}

	return false;
}

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

vector<pair<int, int>>& Bishop::getPosibleMoves()
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

Castle::Castle(int _x, int _y, bool _color, ChessBoard & _board) : Figures(_x, _y, PRIORITY_CASTLE, _color, _board)
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

vector<pair<int, int>>& Castle::getPosibleMoves()
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

Queen::Queen(int _x, int _y, bool _color, ChessBoard & _board) : Figures(_x, _y, PRIORITY_QUEEN, _color, _board)
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

vector<pair<int, int>>& Queen::getPosibleMoves()
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

King::King(int _x, int _y, bool _color, ChessBoard & _board) : Figures(_x, _y, PRIORITY_KING, _color, _board)
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

vector<pair<int, int>>& King::getPosibleMoves()
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
