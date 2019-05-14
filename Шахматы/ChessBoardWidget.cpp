#include "ChessBoardWidget.h"
#include <qpainter.h>
#include <qmessagebox.h>
#include <utility>
#include <random>
#include <ctime>

ChessBoardWidget::ChessBoardWidget(QWidget *parent)
	: QWidget(parent)
{

	setMouseTracking(true);

	brushBlack = QBrush(QColor(0, 0, 0, 200), Qt::SolidPattern);
	brushWhite = QBrush(QColor(0, 0, 0, 100), Qt::SolidPattern);
	brushHighlight = QBrush(QColor(0, 255, 0, 150), Qt::SolidPattern);
	//brushGreen = QBrush(QColor(0, 255, 0, 100), Qt::SolidPattern);
	brushRed = QBrush(QColor(255, 0, 0, 150), Qt::SolidPattern);

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


	QMessageBox msgBox(QMessageBox::Question,
		"Game type",
		"Chose game type",
		QMessageBox::Yes | QMessageBox::No,
		this);
	msgBox.setButtonText(QMessageBox::Yes, "PvP");
	msgBox.setButtonText(QMessageBox::No, "PvE");

	if (msgBox.exec() == QMessageBox::Yes)
		gameType = true;
	else
		gameType = false;

	whatPlayerTurn = false;

}


pair<pair<int, int>, pair<int, int> > ChessBoardWidget::getBotTurn()
{
	vector <pair<pair<int, int>, pair<int, int> > > allMoves;
	vector <pair<pair<int, int>, pair<int, int> > > eatPeaceMoves;
	vector <Figures*> peaceInDanger;

	for (auto i : board.getFigures(whatPlayerTurn))
	{
		for (int x = 0; x < 8; ++x)
			for (int y = 0; y < 8; ++y)
				if (i->checkMove(x, y) && !i->willBeOnCheck(x, y))
					allMoves.push_back(make_pair(make_pair(
						i->getPos().first, i->getPos().second), make_pair(x, y)
					));
		if (i->isInDanger())
			peaceInDanger.push_back(i);
	}
	for (auto i : allMoves)
	{
		if (board[i.first.first][i.first.second]->willBeCheckmate(i.second.first, i.second.second))
			return i;

		if (board[i.second.first][i.second.second] != nullptr)
			eatPeaceMoves.push_back(i);
		else if (board[i.first.first][i.first.second]->getName() == "W_P" ||
			board[i.first.first][i.first.second]->getName() == "B_P")
		{
			Figures* peace = board[i.first.first][i.first.second];
			if (peace->getColor() && peace->getPos().second == 5 &&
				board[peace->getPos().first][4] != nullptr &&
				board[peace->getPos().first][4]->getName() == "B_P" &&
				board[peace->getPos().first][4]->getMovesCounter() == 1)
				eatPeaceMoves.push_back(i);

			if (!peace->getColor() && peace->getPos().second == 2 &&
				board[peace->getPos().first][3] != nullptr &&
				board[peace->getPos().first][3]->getName() == "W_P" &&
				board[peace->getPos().first][3]->getMovesCounter() == 1)
				eatPeaceMoves.push_back(i);
		}
	}
	pair<pair<int, int>, pair<int, int> > bestMove;
	int maxValue = -100;

	for (auto i : eatPeaceMoves)
	{
		if (board[i.first.first][i.first.second]->isInDanger(i.second.first, i.second.second))
			if (board[i.second.first][i.second.second]->getPriority() - board[i.first.first][i.first.second]->getPriority() > maxValue)
			{
				maxValue = board[i.second.first][i.second.second]->getPriority() - board[i.first.first][i.first.second]->getPriority();
				bestMove = i;
			}
	}

	if (maxValue == -100)
	{
		maxValue = 100;
		for (auto i : allMoves)
		{
			if (board[i.first.first][i.first.second]->isInDanger(i.second.first, i.second.second))
			{
				if (board[i.first.first][i.first.second]->getPriority() < maxValue)
				{
					maxValue = board[i.first.first][i.first.second]->getPriority();
					bestMove = i;
				}
			}
			else
			{
				maxValue = 0;
				bestMove = i;
			}
		}
	}
	vector <pair<pair<int, int>, pair<int, int> > > random;
	for (auto i : allMoves)
	{
		if (maxValue == 0)
		{
			if (!board[i.first.first][i.first.second]->isInDanger(i.second.first, i.second.second))
				random.push_back(i);
		}
		else
		{
			if (board[i.first.first][i.first.second]->getPriority() == maxValue)
			{
				random.push_back(i);
			}
		}
	}
	
	srand(time(0));
	return random[rand() % random.size()];
}

void ChessBoardWidget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	currentSize = width() < (height() - 30) ? width() : (height() - 30);
	currentTileSize = currentSize / 8;
	horisontalOffsets = (width() - currentSize) / 2;
	verticalOffsets = (height() - 30 - currentSize) / 2 + 30;

	if (whatPlayerTurn && !board.getWhiteKing()->havePossibleMoves() || !whatPlayerTurn && !board.getBlackKing()->havePossibleMoves())
		close();

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			painter.setBrush((x + y) % 2 == 1 ? brushBlack : brushWhite);

			painter.drawRect(x * currentTileSize + horisontalOffsets, y * currentTileSize + verticalOffsets, currentTileSize, currentTileSize);

			if (board[x][y] == board.getBlackKing() && board.getBlackKing()->isInDanger())
			{
				painter.setBrush(brushRed);
				painter.drawRect(board.getBlackKing()->getPos().first * currentTileSize + horisontalOffsets, (7 - board.getBlackKing()->getPos().second) * currentTileSize + verticalOffsets, currentTileSize, currentTileSize);
			}
			if (board[x][y] == board.getWhiteKing() && board.getWhiteKing()->isInDanger())
			{
				painter.setBrush(brushRed);
				painter.drawRect(board.getWhiteKing()->getPos().first * currentTileSize + horisontalOffsets, (7 - board.getWhiteKing()->getPos().second) * currentTileSize + verticalOffsets, currentTileSize, currentTileSize);
			}

			if (board[x][7 - y] != nullptr && board[x][7 - y] != selectedPiece)
			{
				painter.drawImage(QRect(x * currentTileSize + horisontalOffsets, y * currentTileSize + verticalOffsets, currentTileSize, currentTileSize), pieceImages[board[x][7 - y]->getName()]);
			}
		}
	}
	if (selectedPiece != nullptr)
	{
		painter.setBrush(brushHighlight);

		for (auto i : selectedPiece->getPosibleMoves())
			if (!selectedPiece->willBeOnCheck(i.first, i.second))
				painter.drawRect(i.first * currentTileSize + horisontalOffsets, (7 - i.second) * currentTileSize + verticalOffsets, currentTileSize, currentTileSize);
		
		painter.setOpacity(0.2);
		painter.drawImage(QRect(selectedPiece->getPos().first * currentTileSize + horisontalOffsets, (7 - selectedPiece->getPos().second) * currentTileSize + verticalOffsets, currentTileSize, currentTileSize), pieceImages[selectedPiece->getName()]);
		painter.setOpacity(1);
	}
}


void ChessBoardWidget::mousePressEvent(QMouseEvent* _e)
{
	if (_e->button() == Qt::LeftButton && !gameType)
	{
		auto i = getBotTurn();
		board[i.first.first][i.first.second]->move(i.second.first, i.second.second);
		whatPlayerTurn = !whatPlayerTurn;
		update();
	}


	if (_e->button() == Qt::LeftButton && gameType)
	{
		int x = (_e->x() - horisontalOffsets) / currentTileSize;
		int y = (_e->y() - verticalOffsets) / currentTileSize;

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
			{
				whatPlayerTurn = !whatPlayerTurn;
				if (!gameType)
				{
					auto i = getBotTurn();
					board[i.first.first][i.first.second]->move(i.second.first, i.second.second);
					whatPlayerTurn = !whatPlayerTurn;
				}
			}
			selectedPiece = nullptr;
		}
		update();
	}
}

