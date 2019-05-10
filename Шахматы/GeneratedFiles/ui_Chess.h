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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
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
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    ChessBoardWidget *widget;
    QLabel *label;
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
        widget = new ChessBoardWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 150, 47, 13));

        verticalLayout->addWidget(widget);

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
        label->setText(QApplication::translate("ChessClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChessClass: public Ui_ChessClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESS_H
