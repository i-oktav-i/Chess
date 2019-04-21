#pragma once

#include "Figures.h"

class Pawn : public Figures
{

public:

	Pawn(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() const override;

private:

	void reborn();

};