#include "Figures.h"

Figures::Figures(int _x, int _y, bool _color, ChessBoard * _board)
{
	xPos = _x;
	yPos = _y;
	color = _color;
	board = _board;
}

Pawn::Pawn(int _x, int _y, bool _color, ChessBoard * _board) : Figures(_x, _y, _color, _board)
{
	if (_color)
		name = "W_P";
	else
		name = "B_P";
}

Knight::Knight(int _x, int _y, bool _color, ChessBoard * _board) : Figures(_x, _y, _color, _board)
{
	if (_color)
		name = "W_K";
	else
		name = "B_K";
}
