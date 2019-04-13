#pragma once

#include "ChessBoard.h"
#include <string>
#include <vector>
#include <utility>

using namespace std;


class ChessBoard;

class TurnsCounter;


class Figures
{

public:

	pair<int, int> getPos() { return pair<int, int>(xPos, yPos); }

	bool getColor() { return color; };
	
	string getName() { return name; };
	
	int getPriority() { return priority; }

	bool getIsDead() { return isDead; }

	bool getIsMoved() { return isMoved; }

	virtual bool move(int, int);

	virtual bool checkMove(int, int) const = 0;
	
	virtual vector<pair<int, int> >& getPosibleMoves() = 0;

	vector<pair<int, int> >& getEatFigureMoves();

	bool isInDanger();

	bool isInDanger(int, int);

protected:

	Figures(int, int, int, bool, ChessBoard&, TurnsCounter&);

	void setPos(int, int);

	int xPos;
	int yPos;

	int priority;
	//pair<int, int> pos;

	bool color;
	bool isMoved = false;
	bool isDead = false;
	string name;
	ChessBoard& board;
	int turnOfLastMove = 0;
	TurnsCounter& turnsCounter;

};

class Pawn : public Figures
{

public:

	Pawn(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() override;

private:

	void reborn();

};

class Knight : public Figures
{

public:

	Knight(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() override;

};

class Bishop : public Figures
{

public:

	Bishop(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() override;

};

class Castle : public Figures
{

public:

	Castle(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() override;

};

class Queen : public Figures
{

public:

	Queen(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() override;

};

class King : public Figures
{

public:

	King(int, int, int, bool, ChessBoard&, TurnsCounter&);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() override;

	bool isCheck(int, int) const;
	bool isCheckmate();

};
