#include "Figures.h"
#include "ChessBoard.h"
#include <iostream>

using namespace std;

void PvPGame()
{
	ChessBoard board;
	
	bool whosTurn = true;

	Figures* currFig;
	
	bool flag = true;

	while (flag)
	{

		system("cls");

		if ((whosTurn && board.getWhiteKing()->havePossibleMoves()) || (!whosTurn && board.getBlackKing()->havePossibleMoves()))
		{
			board.show();
			cout << endl
			<< "Chose figure position(column and row): ";

			int x, y;
			while (!(cin >> x >> y) || x < 1 || x > 8 || y < 1 || y > 8 || board[x - 1][y - 1] == nullptr || board[x - 1][y - 1]->getColor() != whosTurn)
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
		else
		{
			if ((whosTurn && board.getWhiteKing()->isInDanger()) || (!whosTurn && board.getBlackKing()->isInDanger()))
			{
				if (whosTurn)
					cout << "Black ";
				else
					cout << "White ";
				cout << "player win" << endl;
			}
			else
				cout << "DRAW";
			flag = false;
		}
	}
}

int main()
{

	PvPGame();

	system("pause");

	return 0;
}