#include "Chess.h"
#include <QtWidgets/QApplication>
#include "Figures.h"
#include "ChessBoard.h"
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Chess w;
	w.show();
	return a.exec();
}
