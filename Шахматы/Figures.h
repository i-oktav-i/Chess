#pragma once

#include "ChessBoard.h"
#include <string>
#include <vector>
#include <utility>

using namespace std;


class ChessBoard;


class Figures
{

public:
	
	Figures(int, int, int, bool, ChessBoard&);

	pair<int, int> getPos() { return pair<int, int>(xPos, yPos); }

	bool getColor() { return color; };
	
	string getName() { return name; };
	
	int getPriority() { return priority; }

	bool getIsDead() { return isDead; }

	bool getIsMoved() { return isMoved; }

	virtual bool move(int _x, int _y) = 0;

	virtual bool checkMove(int, int) const = 0;
	
	virtual vector<pair<int, int> >& getPosibleMoves() = 0;

	vector<pair<int, int> >& getEatFigureMoves();

	bool isInDanger();
	bool isInDanger(int, int);

	void setPos(int, int);

protected:
	
	int priority;
	int xPos;
	int yPos;
	//pair<int, int> pos;
	bool color;
	bool isMoved = false;
	bool isDead = false;
	string name;
	ChessBoard& board;

};

class Pawn : public Figures
{

public:

	Pawn(int, int, bool, ChessBoard&);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() override;

private:

	void reborn();

};

class Knight : public Figures
{

public:

	Knight(int, int, bool, ChessBoard&);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() override;

};

class Bishop : public Figures
{

public:

	Bishop(int, int, bool, ChessBoard &);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() override;

};

class Castle : public Figures
{

public:
	
	Castle(int, int, bool, ChessBoard &);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() override;

};

class Queen : public Figures
{

public:
	
	Queen(int, int, bool, ChessBoard &);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() override;

};

class King : public Figures
{

public:
	
	King(int, int, bool, ChessBoard &);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

	vector<pair<int, int> >& getPosibleMoves() override;

	bool isCheck(int, int) const;
	bool isCheckmate();

};
