/********************************************************************************
** Form generated from reading UI file 'Chess.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESS_H
#define UI_CHESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <chessboardwidget.h>

QT_BEGIN_NAMESPACE

class Ui_ChessClass
{
public:
    QAction *actionRestart;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    ChessBoardWidget *chessBoard;
    QGridLayout *gridLayout;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChessClass)
    {
        if (ChessClass->objectName().isEmpty())
            ChessClass->setObjectName(QString::fromUtf8("ChessClass"));
        ChessClass->resize(800, 800);
        ChessClass->setMinimumSize(QSize(0, 0));
        actionRestart = new QAction(ChessClass);
        actionRestart->setObjectName(QString::fromUtf8("actionRestart"));
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

        verticalLayout->addWidget(chessBoard);

        ChessClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ChessClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        ChessClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChessClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ChessClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ChessClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ChessClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionRestart);

        retranslateUi(ChessClass);
        QObject::connect(actionRestart, SIGNAL(triggered()), chessBoard, SLOT(restart()));

        QMetaObject::connectSlotsByName(ChessClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChessClass)
    {
        ChessClass->setWindowTitle(QApplication::translate("ChessClass", "Chess", nullptr));
        actionRestart->setText(QApplication::translate("ChessClass", "Restart", nullptr));
        menu->setTitle(QApplication::translate("ChessClass", "Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChessClass: public Ui_ChessClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESS_H
