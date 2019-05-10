#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Chess.h"
#include "ChessBoard.h"
#include <map>
#include <qwidget.h>
#include <qbrush.h>
#include <qimage.h>
#include <qmouseeventtransition.h>

class Chess : public QMainWindow
{
	Q_OBJECT

public:
	Chess(QWidget *parent = Q_NULLPTR);

private:
	Ui::ChessClass ui;
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
};
