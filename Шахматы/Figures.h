#pragma once

#include "ChessBoard.h"
#include "TurnsCounter.h"
#include <string>
#include <vector>
#include <utility>

using namespace std;


class ChessBoard;

class TurnsCounter;


class Figures
{

public:

	pair<int, int> getPos() const { return pair<int, int>(xPos, yPos); }

	bool getColor() const { return color; };
	
 	string getName() const { return name; };
	
	int getPriority() const { return priority; }

	bool getIsDead() const { return isDead; }

	bool getIsMoved() const { return isMoved; }

	int getTurnOfLastMove() const { return turnOfLastMove; }

	int getMovesCounter() const { return movesCounter; }

	virtual bool move(int, int);

	virtual bool checkMove(int, int) const = 0;
	
	virtual vector<pair<int, int> >& getPosibleMoves() const;

	vector<pair<int, int> >& getEatPieceMoves() const;

	bool isInDanger() const;

	bool isInDanger(int, int) const;

	int getTurnNumber() const { return turnsCounter.getCount(); }

protected:

	Figures(int, int, int, bool, ChessBoard&, TurnsCounter&);

	void setPos(int, int);

	int xPos;
	int yPos;

	int priority;

	bool color;
	bool isMoved = false;
	bool isDead = false;
	string name;
	ChessBoard& board;
	int turnOfLastMove = 0;
	int movesCounter = 0;
	TurnsCounter& turnsCounter;

};

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

class Knight : public Figures
{

public:

	Knight(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() const override;

};

class Bishop : public Figures
{

public:

	Bishop(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() const override;

};

class Castle : public Figures
{

public:

	Castle(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() const override;

};

class Queen : public Figures
{

public:

	Queen(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() const override;

};

class King : public Figures
{

public:

	King(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() const override;

	bool isCheck(int, int) const;
	bool isCheckmate() const;

	bool longRoque() const;
	bool shortRoque() const;

};
