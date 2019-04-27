#include "ChessBoardWidget.h"
#include <qpainter.h>

ChessBoardWidget::ChessBoardWidget(QWidget *parent)
	: QWidget(parent)
{
	setMouseTracking(true);

	brushBlack = QBrush(QColor(0, 0, 0, 200), Qt::SolidPattern);
	brushWhite = QBrush(QColor(0, 0, 0, 100), Qt::SolidPattern);
	brushHighlight = QBrush(QColor(255, 0, 255, 150), Qt::SolidPattern);

	QImage sheet("./Resources/chess_pieces.png");

	Q_ASSERT(!sheet.isNull());

	int pieceWidth = 333;
	int pieceHeight = 333;

	pieceImages["W_K"] = sheet.copy(pieceWidth * 0, 0, pieceWidth, pieceHeight);
	pieceImages["W_Q"] = sheet.copy(pieceWidth * 1, 0, pieceWidth, pieceHeight);
	pieceImages["W_B"] = sheet.copy(pieceWidth * 2, 0, pieceWidth, pieceHeight);
	pieceImages["W_H"] = sheet.copy(pieceWidth * 3, 0, pieceWidth, pieceHeight);
	pieceImages["W_C"] = sheet.copy(pieceWidth * 4, 0, pieceWidth, pieceHeight);
	pieceImages["W_P"] = sheet.copy(pieceWidth * 5, 0, pieceWidth, pieceHeight);

	pieceImages["B_K"] = sheet.copy(pieceWidth * 0, pieceHeight, pieceWidth, pieceHeight);
	pieceImages["B_Q"] = sheet.copy(pieceWidth * 1, pieceHeight, pieceWidth, pieceHeight);
	pieceImages["B_B"] = sheet.copy(pieceWidth * 2, pieceHeight, pieceWidth, pieceHeight);
	pieceImages["B_H"] = sheet.copy(pieceWidth * 3, pieceHeight, pieceWidth, pieceHeight);
	pieceImages["B_C"] = sheet.copy(pieceWidth * 4, pieceHeight, pieceWidth, pieceHeight);
	pieceImages["B_P"] = sheet.copy(pieceWidth * 5, pieceHeight, pieceWidth, pieceHeight);

	whatPlayerTurn = false;
}


void ChessBoardWidget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	currentSize = width() < height() ? width() : height();;
	currentTileSize = currentSize / 8;
	horisontalOffsets = (width() - currentSize) / 2;
	verticalOffsets = (height() - currentSize) / 2;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			painter.setBrush((x + y) % 2 == 1 ? brushBlack : brushWhite);
/*
			if (x == 0 && y == 0)
				painter.setBrush(brushHighlight);*/

			painter.drawRect(x * currentTileSize + horisontalOffsets, y * currentTileSize + verticalOffsets, currentTileSize, currentTileSize);

			if(board[x][7 - y] != nullptr && board[x][7 - y] != selectedPiece)
				painter.drawImage(QRect(x * currentTileSize + horisontalOffsets, y * currentTileSize + verticalOffsets, currentTileSize, currentTileSize), pieceImages[board[x][7 - y]->getName()]);
		}
	}
	if (selectedPiece != nullptr)
	{
		painter.setBrush(brushHighlight);
		for (auto i : selectedPiece->getPosibleMoves())
			painter.drawRect(i.first * currentTileSize + horisontalOffsets, (7 - i.second) * currentTileSize + verticalOffsets, currentTileSize, currentTileSize);
	}
}

void ChessBoardWidget::mousePressEvent(QMouseEvent* _e)
{
	int x = _e->x() / currentTileSize;
	int y = _e->y() / currentTileSize;

	if (selectedPiece == nullptr)
	{
		if (board[x][7 - y] != nullptr
			&& board[x][7 - y]->getColor() == whatPlayerTurn
			&& board[x][7 - y]->havePossibleMoves())
			selectedPiece = board[x][7 - y];
	}
	else
	{
		if (selectedPiece->move(x, 7 - y))
			whatPlayerTurn = !whatPlayerTurn;

		selectedPiece = nullptr;
	}
	update();
}

