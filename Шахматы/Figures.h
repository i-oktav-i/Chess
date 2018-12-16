#ifndef FIGURES_H
#define FIGURES_H

#include <string>
#include "ChessBoard.h"

using namespace std;

class Figures
{
public:
	Figures(int, int, bool, ChessBoard*);
	bool getColor() { return color; };
	string getName() { return name; };
	virtual void move(int, int) {};
	virtual bool checkMove(int, int) {};

protected:
	int xPos;
	int yPos;
	bool color;
	bool isMoved = false;
	string name;
	ChessBoard* board;
};

class Pawn : public Figures
{
public:
	Pawn(int, int, bool, ChessBoard*);
	void move(int, int) override;
	bool checkMove(int, int) override;

private:

};

class Knight : public Figures
{
public:
	Knight(int, int, bool, ChessBoard*);
	~Knight();
	void move(int, int) override;
	bool checkMove(int, int) override;

};

class Bishop : public Knight
{
public:
	Bishop();
	~Bishop();
	void move(int, int) override;
	bool checkMove(int, int) override;

private:

};
class Castle : public Figures
{

public:
	Castle();
	~Castle();
	void move(int, int) override;
	bool checkMove(int, int) override;

private:

};

class Queen : Figures
{
public:
	Queen();
	~Queen();
	void move(int, int) override;
	bool checkMove(int, int) override;

private:

};

class King : Figures
{
public:
	King();
	~King();
	void move(int, int) override;
	bool checkMove(int, int) override;

private:

};



#endif // !FIGURES_H