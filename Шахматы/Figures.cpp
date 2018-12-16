#include "Figures.h"
#include <math.h>
#include <iostream>

Figures::Figures(int _x, int _y, bool _color, ChessBoard * _board)
{
	xPos = _x;
	yPos = _y;
	color = _color;
	board = _board;
}

inline void Figures::remove(int _x, int _y)
{
	board->board[_x][_y] = board->board[xPos][yPos];
	board->board[xPos][yPos] = nullptr;
	xPos = _x;
	yPos = _y;
	isMoved = true;
}

Pawn::Pawn(int _x, int _y, bool _color, ChessBoard * _board) : Figures(_x, _y, _color, _board)
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
		remove(_x, _y);

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
		if ((color && (_y - yPos) == 1 && (board->board[_x][_y] == nullptr || !board->board[_x][_y]->getColor()))
			|| (color && (_y - yPos) == 2 && !isMoved && (board->board[_x][_y] == nullptr || !board->board[_x][_y]->getColor()))
			|| (!color && (_y - yPos) == -1 && (board->board[_x][_y] == nullptr || board->board[_x][_y]->getColor()))
			|| (!color && (_y - yPos) == -2 && !isMoved && (board->board[_x][_y] == nullptr || board->board[_x][_y]->getColor())))
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
		board->board[xPos][yPos] = new Queen(xPos, yPos, color, board);
		break;
	case 2:
		board->board[xPos][yPos] = new Knight(xPos, yPos, color, board);
		break;
	case 3:
		board->board[xPos][yPos] = new Bishop(xPos, yPos, color, board);
		break;
	case 4:
		board->board[xPos][yPos] = new Castle(xPos, yPos, color, board);
		break;
	case 0:
	default:
		break;
	}
}

Knight::Knight(int _x, int _y, bool _color, ChessBoard * _board) : Figures(_x, _y, _color, _board)
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
		remove(_x, _y);
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
				board->board[_x][_y] == nullptr ||
				board->board[_x][_y]->getColor() != color
				)
			)
		|| (
			abs(_x - xPos) == 1 &&
			abs(_y - yPos) == 2 && (
				board->board[_x][_y] == nullptr ||
				board->board[_x][_y]->getColor() != color
				)
			)
		)
		return true;

	return false;
}

Bishop::Bishop(int _x, int _y, bool _color, ChessBoard * _board) : Figures(_x, _y, _color, _board)
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
		remove(_x, _y);
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
		
		while (_y != _yPos && board->board[_xPos][_yPos] == nullptr)
		{
			_yPos += dY;
			_xPos += dX;
		}
		if (_y == _yPos && (board->board[_x][_y] == nullptr || board->board[_x][_y]->getColor() != color))
			return true;
	}

	return false;
}

Castle::Castle(int _x, int _y, bool _color, ChessBoard * _board) : Figures(_x, _y, _color, _board)
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
		remove(_x, _y);
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

		while ((_y != _yPos || _x != _xPos) && board->board[_xPos][_yPos] == nullptr)
		{
			_yPos += dY;
			_xPos += dX;
		}
		if (_y == _yPos && _x == _xPos && (board->board[_x][_y] == nullptr || board->board[_x][_y]->getColor() != color))
			return true;
	}

	return false;
}

Queen::Queen(int _x, int _y, bool _color, ChessBoard * _board) : Figures(_x, _y, _color, _board)
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
		remove(_x, _y);
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

		while ((_y != _yPos || _x != _xPos) && board->board[_xPos][_yPos] == nullptr)
		{
			_yPos += dY;
			_xPos += dX;
		}
		if (_y == _yPos && _x == _xPos && (board->board[_x][_y] == nullptr || board->board[_x][_y]->getColor() != color))
			return true;
	}

	return false;
}

King::King(int _x, int _y, bool _color, ChessBoard * _board) : Figures(_x, _y, _color, _board)
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
		remove(_x, _y);
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
			board->board[_x][_y] == nullptr || board->board[_x][_y]->getColor() != color
			)
		)
		return true;

	return false;
}
