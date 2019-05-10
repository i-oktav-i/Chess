#include "Chess.h"
#include <qpainter.h>

Chess::Chess(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.turns->setMaximumHeight(30);
}

void Chess::paintEvent(QPaintEvent*)
{
	ui.turns->setText(QString::number(ui.chessBoard->getTurn() + 1));
}
