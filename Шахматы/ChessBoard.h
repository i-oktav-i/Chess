#pragma once

#include <vector>
#include "Figures.h"
#include "TurnsCounter.h"

using namespace std;

class TurnsCounter;

class Figures;

class ChessBoard
{
public:

	ChessBoard();

	ChessBoard(const ChessBoard&);

	~ChessBoard();

	void show() const;
	
	const vector<Figures*>& getFigures() const;

	Figures* findeFigure(pair<int, int>);
	
	Figures ** operator[] (int);

	Figures* getWhiteKing() const { return whiteKing; }
	Figures* getBlackKing() const { return blackKing; }

private:

	Figures*** board;

	bool playerColor;

	vector<Figures*> figures;

	TurnsCounter turnsCounter;

	Figures *whiteKing, *blackKing;

};