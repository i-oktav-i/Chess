#pragma once

#include "ChessBoard.h"
//#include <QWidget>
//#include <QBrush>
//#include <QImage>
//#include <QMouseEvent>
#include <qwidget.h>
#include <qbrush.h>
#include <qimage.h>
//#include <qmouseeventtransition.h>
#include <qevent.h>
#include <map>
#include <qlabel.h>


class ChessBoardWidget : public QWidget
{
	Q_OBJECT

public:
	ChessBoardWidget(QWidget *parent = nullptr);
	~ChessBoardWidget() {};

	int getTurn() { return board.getTurn(); }

private:
	int currentSize;
	int currentTileSize;
	int horisontalOffsets;
	int verticalOffsets;
	ChessBoard board;
	QBrush brushWhite;
	QBrush brushBlack;
	QBrush brushGreen;
	QBrush brushRed;
	QBrush brushHighlight;
	map<string, QImage> pieceImages;
	Figures* selectedPiece = nullptr;
	bool whatPlayerTurn;

	bool gameType;

	QLabel turns;
	//void resizeEvent(QResizeEvent*) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
	//void mouseMoveEvent(QMouseEvent*) Q_DECL_OVERRIDE;
};
