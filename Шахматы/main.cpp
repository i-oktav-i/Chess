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
		while (!(cin >> x >> y) || board.board[x - 1][y - 1] == nullptr || board.board[x - 1][y - 1]->getColor() != whosTurn)
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Chose figure position(row and column): ";
		}
		currFig = board.board[x - 1][y - 1];


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

	system("pause");

	return 0;
}