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
			<< "Chose figure position(column and row): ";
		
		int x, y;
		while (!(cin >> x >> y) || x < 0 || x > 7 || y < 0 || y > 7 || board[x - 1][y - 1] == nullptr || board[x - 1][y - 1]->getColor() != whosTurn)
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Chose figure position(column and row): ";
		}
		currFig = board[x - 1][y - 1];


		cout << "Chose position to move(column and row): ";

		while (!(cin >> x >> y))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Chose position to move(column and row): ";
		}
		if (currFig->move(x - 1, y - 1))
			whosTurn = !whosTurn;
	}
}

int main()
{

	PvPGame();

	system("pause");

	return 0;
}