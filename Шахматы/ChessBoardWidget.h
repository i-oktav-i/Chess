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


class ChessBoardWidget : public QWidget
{
	Q_OBJECT

public:
	ChessBoardWidget(QWidget *parent = nullptr);
	~ChessBoardWidget() {};
private:
	int currentSize;
	int currentTileSize;
	int horisontalOffsets;
	int verticalOffsets;
	ChessBoard board;
	QBrush brushWhite;
	QBrush brushBlack;
	QBrush brushHighlight;
	map<string, QImage> pieceImages;
	Figures* selectedPiece = nullptr;
	bool whatPlayerTurn;
protected:
	//void resizeEvent(QResizeEvent*) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
	//void mouseMoveEvent(QMouseEvent*) Q_DECL_OVERRIDE;
};
