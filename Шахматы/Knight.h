#pragma once
#include "Figures.h"

class Knight : public Figures
{

public:

	Knight(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() const override;

};