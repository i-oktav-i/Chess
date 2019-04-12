#pragma once

#include <vector>
#include "Figures.h"

using namespace std;

class Figures;

class ChessBoard
{
public:

	ChessBoard();

	~ChessBoard();

	void show() const;
	
	const vector<Figures*>& getFigures() const;

	Figures* findeFigure(pair<int, int>);
	
	Figures ** operator[] (int);


private:

	Figures*** board;

	bool playerColor;

	vector<Figures*> figures;
};