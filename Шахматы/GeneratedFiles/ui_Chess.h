/********************************************************************************
** Form generated from reading UI file 'Chess.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESS_H
#define UI_CHESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <chessboardwidget.h>

QT_BEGIN_NAMESPACE

class Ui_ChessClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    ChessBoardWidget *chessBoard;
    QGridLayout *gridLayout;
    QLabel *turns;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChessClass)
    {
        if (ChessClass->objectName().isEmpty())
            ChessClass->setObjectName(QString::fromUtf8("ChessClass"));
        ChessClass->resize(800, 800);
        ChessClass->setMinimumSize(QSize(0, 0));
        centralWidget = new QWidget(ChessClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        chessBoard = new ChessBoardWidget(centralWidget);
        chessBoard->setObjectName(QString::fromUtf8("chessBoard"));
        gridLayout = new QGridLayout(chessBoard);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        turns = new QLabel(chessBoard);
        turns->setObjectName(QString::fromUtf8("turns"));
        turns->setMaximumSize(QSize(16777215, 30));

        gridLayout->addWidget(turns, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        verticalLayout->addWidget(chessBoard);

        ChessClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ChessClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        ChessClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChessClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ChessClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ChessClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ChessClass->setStatusBar(statusBar);

        retranslateUi(ChessClass);

        QMetaObject::connectSlotsByName(ChessClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChessClass)
    {
        ChessClass->setWindowTitle(QApplication::translate("ChessClass", "Chess", nullptr));
        turns->setText(QApplication::translate("ChessClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChessClass: public Ui_ChessClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESS_H
