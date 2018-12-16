#pragma once

#include <string>

using namespace std;


class Figures;


class ChessBoard
{
public:
	ChessBoard();
	~ChessBoard();
	void show();
	Figures* board[8][8];
	Figures** operator[] (int);

private:

};


class Figures
{
public:
	Figures(int, int, bool, ChessBoard*);
	inline bool getColor() { return color; };
	inline string getName() { return name; };
	virtual bool move(int _x, int _y) { return true; };
	virtual bool checkMove(int, int) const { return true; };
	void remove(int, int);

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
	bool move(int, int) override;
	bool checkMove(int, int) const override;

private:
	void reborn();
};

class Knight : public Figures
{
public:
	Knight(int, int, bool, ChessBoard*);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

};

class Bishop : public Figures
{
public:
	Bishop(int, int, bool, ChessBoard *);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

private:

};

class Castle : public Figures
{

public:
	Castle(int, int, bool, ChessBoard *);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

private:

};

class Queen : public Figures
{
public:
	Queen(int, int, bool, ChessBoard *);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

private:

};

class King : public Figures
{
public:
	King(int, int, bool, ChessBoard *);
	bool move(int, int) override;
	bool checkMove(int, int) const override;

private:

};


