#include "Figures.h"
#include "ChessBoard.h"
#include <iostream>

using namespace std;

void PvPGame()
{
	ChessBoard board;
	
	bool whosTurn = true;

	Figures* currFig;
	
	while (true)
	{
		system("cls");
		board.show();
		cout << endl
			<< "Chose figure position(row and column): ";
		
		int x, y;
		while (!(cin >> x >> y) || x < 0 || x > 7 || y < 0 || y > 7 || board[x - 1][y - 1] == nullptr || board[x - 1][y - 1]->getColor() != whosTurn)
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Chose figure position(row and column): ";
		}
		currFig = board[x - 1][y - 1];


		cout << "Chose position to move(row and column): ";

		while (!(cin >> x >> y) || !currFig->move(x - 1, y - 1))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Chose position to move(row and column): ";
		}

		whosTurn = !whosTurn;
	}
}

int main()
{

	PvPGame();
/*
	vector<pair<int, int>> a, b;
	a.push_back(pair<int, int>(5, 6));
	a.push_back(pair<int, int>(1, 9));

	b.push_back(pair<int, int>(5, 6));
	b.push_back(pair<int, int>(5, 6));
	
	cout << a + b;*/
	system("pause");

	return 0;
}