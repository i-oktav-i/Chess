#include "Chess.h"
#include <qpainter.h>

Chess::Chess(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void Chess::paintEvent(QPaintEvent*)
{
}
