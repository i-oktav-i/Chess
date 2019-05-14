#include "AIplayer.h"



Player::Player(ChessBoard& _board) : board(_board)
{
}


void AIPlayer::takeTurn()
{
	auto movebleFigures = getMovebleFigures();
	auto figuresInDanger = getFiguresInDanger();
	auto killebleFigures = getKillebleFigures();
	auto killFiguresFigures = getKillFiguresFigures();

	vector<Move> potencialMoves;

	for (auto i : killFiguresFigures)
	{
		auto eatFigureMoves = i->getEatPieceMoves();

	}
}

vector<Figures*>& AIPlayer::getMovebleFigures()
{
	vector<Figures*> figures;
	/*for (auto i : board.getFigures())
	{
		if (i->getPosibleMoves().size() > 0)
			figures.push_back(i);
	}
*/
	return figures;
}

vector<Figures*>& AIPlayer::getFiguresInDanger()
{
	vector<Figures*> figuresInDanger;
/*
	for (auto i : board.getFigures())
	{
		if (i->getColor() == playerColor && i->isInDanger())
			figuresInDanger.push_back(i);
	}*/

	return figuresInDanger;
}

vector<Figures*>& AIPlayer::getKillebleFigures()
{
	vector<Figures*> killebleFigures;
/*
	for (auto i : board.getFigures())
	{
		if (i->getColor() != playerColor && i->isInDanger())
			killebleFigures.push_back(i);
	}*/

	return killebleFigures;
}

vector<Figures*>& AIPlayer::getKillFiguresFigures()
{
	vector<Figures*> killFiguresFigures;
/*
	for (auto i : board.getFigures())
	{
		if (i->getColor() == playerColor && i->getEatPieceMoves().size() != 0)
			killFiguresFigures.push_back(i);
	}*/

	return killFiguresFigures;
}

Move::Move(Figures * _figure, pair<int, int> _movePos)
{
	figure = _figure;
	movePos = _movePos;
}
