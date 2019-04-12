#pragma once

#include "ChessBoard.h"
#include <vector>

class Player
{
public:

	Player(ChessBoard&);

protected:
	
	bool playerColor;
	
	ChessBoard& board;
};

class AIPlayer : public Player
{
public:
	AIPlayer();

	void takeTurn();

private:
	vector<Figures*>& getMovebleFigures();
	vector<Figures*>& getFiguresInDanger();
	vector<Figures*>& getKillebleFigures();
	vector<Figures*>& getKillFiguresFigures();
};

class Move
{
public:
	Move(Figures*, pair<int, int>);

	Figures* getFigure() { return figure; }
	pair<int, int> getMovePos() { return movePos; }

private:
	
	Figures* figure;
	pair<int, int> movePos;

};
