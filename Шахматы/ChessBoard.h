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

	~ChessBoard();
	
	const vector<Figures*> getFigures(bool) const;
	
	Figures ** operator[] (int);

	Figures* getWhiteKing() const { return whiteKing; }
	
	Figures* getBlackKing() const { return blackKing; }

	int getTurn() { return turnsCounter.getCount(); }

private:

	Figures*** board;

	bool playerColor;

	TurnsCounter turnsCounter;

	Figures *whiteKing, *blackKing;

};