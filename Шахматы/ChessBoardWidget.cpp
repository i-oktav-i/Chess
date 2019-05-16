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

	restart();
}


void ChessBoardWidget::restart()
{
	gameEnd = false;
	selectedPiece = nullptr;
	board.restart();
	QMessageBox choseType(this);
	choseType.setText("Select game type");

	QPushButton* PvP = choseType.addButton(tr("PvP"), QMessageBox::NoRole);
	QPushButton* PvE = choseType.addButton(tr("PvE"), QMessageBox::NoRole);
	QPushButton* EvE = choseType.addButton(tr("EvE"), QMessageBox::NoRole);

	gameType = choseType.exec();

	if (gameType == 1)
	{
		QMessageBox whoFirst(this);
		whoFirst.setText("Choose who goes first");
		QPushButton* me = whoFirst.addButton(tr("Me"), QMessageBox::NoRole);
		QPushButton* bot = whoFirst.addButton(tr("Bot"), QMessageBox::NoRole);
		QPushButton* rng = whoFirst.addButton(tr("HOLY RANDOM!!!"), QMessageBox::NoRole);

		int reply = whoFirst.exec();
		if (reply == 0)
		{
			botColor = false;
		}
		else if (reply == 1)
		{
			botColor = true;
		}
		else
		{
			srand(time(0));
			botColor = rand() % 2;
		}
	}
	
	
	whatPlayerTurn = true;
	lastTurn = 0;
	gameEnd = true;
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
		else if (board[i.first.first][i.first.second]->getName() == "W_P" && 
			board[i.first.first][i.first.second]->getPos().second == 4 
			||
			board[i.first.first][i.first.second]->getName() == "B_P" &&
			board[i.first.first][i.first.second]->getPos().second == 3)
		{
			Figures* peace = board[i.first.first][i.first.second];
			if (peace->getColor() &&
				board[i.second.first][4] != nullptr &&
				board[i.second.first][4]->getName() == "B_P" &&
				board[i.second.first][4]->getMovesCounter() == 1)
				eatPeaceMoves.push_back(i);

			if (!peace->getColor() &&
				board[i.second.first][3] != nullptr &&
				board[i.second.first][3]->getName() == "W_P" &&
				board[i.second.first][3]->getMovesCounter() == 1)
				eatPeaceMoves.push_back(i);
		}
	}
	pair<pair<int, int>, pair<int, int> > bestMove;
	int maxValue = -100;

	for (auto i : eatPeaceMoves)
	{
		if (board[i.first.first][i.first.second]->getName() == "W_P" &&
			board[i.first.first][i.first.second]->getPos().second == 4
			||
			board[i.first.first][i.first.second]->getName() == "B_P" &&
			board[i.first.first][i.first.second]->getPos().second == 3)
		{
			Figures* peace = board[i.first.first][i.first.second];
			if ((peace->getColor() &&
				board[i.second.first][4] != nullptr &&
				board[i.second.first][4]->getName() == "B_P" &&
				board[i.second.first][4]->getMovesCounter() == 1)
				||
				(!peace->getColor() &&
					board[i.second.first][3] != nullptr &&
					board[i.second.first][3]->getName() == "W_P" &&
					board[i.second.first][3]->getMovesCounter() == 1))
				if (board[i.first.first][i.first.second]->isInDanger(i.second.first, i.second.second))
				{
					if (maxValue < 0)
					{
						maxValue = 0;
						bestMove = i;
					}
				}
				else if (board[i.first.first][i.first.second]->getPriority() > maxValue)
				{
					maxValue = board[i.first.first][i.first.second]->getPriority();
					bestMove = i;
				}
		}
		else
			if (board[i.first.first][i.first.second]->isInDanger(i.second.first, i.second.second))
			{
				if (board[i.second.first][i.second.second]->getPriority() - board[i.first.first][i.first.second]->getPriority() > maxValue)
				{
					maxValue = board[i.second.first][i.second.second]->getPriority() - board[i.first.first][i.first.second]->getPriority();
					bestMove = i;
				}
			}
			else if (board[i.second.first][i.second.second]->getPriority() > maxValue)
			{
				maxValue = board[i.second.first][i.second.second]->getPriority();
				bestMove = i;
			}
	}


	if (maxValue != -100)
		return bestMove;

	Figures* king;
	if (whatPlayerTurn)
		king = board.getWhiteKing();
	else
		king = board.getBlackKing();

	if (king->isInDanger())
	{
		srand(time(0));
		return allMoves[rand() % allMoves.size()];
	}

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

	vector <pair<pair<int, int>, pair<int, int> > > useless;
	for (auto i : allMoves)
	{
		if (maxValue == 0)
		{
			if (!board[i.first.first][i.first.second]->isInDanger(i.second.first, i.second.second))
				useless.push_back(i);
		}
		else if (board[i.first.first][i.first.second]->getPriority() == maxValue)
		{
			useless.push_back(i);
		}
	}
	
	float bestPos = -6.0;

	vector <pair<pair<int, int>, pair<int, int> > > random;

	for (auto i : useless)
	{
		if (board[i.first.first][i.first.second]->getPosPriority(i.second.first, i.second.second) > bestPos)
		{
			bestPos = board[i.first.first][i.first.second]->getPosPriority(i.second.first, i.second.second);
		}
	}

	while (random.size() == 0)
	{
		for (auto i : useless)
		{
			srand(time(0));
			float noize = (float)((rand() % 6000) + 9000) / 1000;

			if (board[i.first.first][i.first.second]->getPosPriority(i.second.first, i.second.second) * noize >= bestPos)
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
	if(gameEnd)
		if ((lastTurn != board.getTurn() && (whatPlayerTurn && !board.getWhiteKing()->havePossibleMoves() || !whatPlayerTurn && !board.getBlackKing()->havePossibleMoves())))
		{
			gameEnd = false;
			if (whatPlayerTurn && board.getWhiteKing()->isInDanger())
				QMessageBox::about(this, "End", "Black win!!!");
			else if (!whatPlayerTurn && board.getBlackKing()->isInDanger())
				QMessageBox::about(this, "End", "White win!!!");
			else
				QMessageBox::about(this, "End", "Draw!!!");
			restart();
		}
		else
		{
			lastTurn = board.getTurn();
		}

	if (gameEnd && board.getFigures().size() == 2)
	{
		gameEnd = false;
		QMessageBox::about(this, "End", "Draw!!!");
	}


	QPainter painter(this);

	currentSize = width() < (height() - 30) ? width() : (height() - 30);
	currentTileSize = currentSize / 8;
	horisontalOffsets = (width() - currentSize) / 2;
	verticalOffsets = (height() - 30 - currentSize) / 2 + 30;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			if ((x + y) % 2 == 1)
				painter.setBrush(brushBlack);
			else
				painter.setBrush(brushWhite);

			//painter.setBrush((x + y) % 2 == 1 ? brushBlack : brushWhite);

			int _X = x * currentTileSize + horisontalOffsets;
			int _Y = y * currentTileSize + verticalOffsets;
			//painter.drawRect(x * currentTileSize + horisontalOffsets, y * currentTileSize + verticalOffsets, currentTileSize, currentTileSize);

			painter.drawRect(_X, _Y, currentTileSize, currentTileSize);

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
	painter.drawText(width() / 2, 15, "Turn number: " + QString::number(board.getTurn()));


	if (gameEnd && gameType == 1 && botColor == whatPlayerTurn)
	{
		auto i = getBotTurn();
		board[i.first.first][i.first.second]->move(i.second.first, i.second.second);
		whatPlayerTurn = !whatPlayerTurn;
		update();
	}

}


void ChessBoardWidget::mousePressEvent(QMouseEvent* _e)
{
	if (_e->button() == Qt::LeftButton)
	{
		if (gameType != 2)
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
				}
				selectedPiece = nullptr;
			}
			update();
		}
		else
		{
			auto i = getBotTurn();
			board[i.first.first][i.first.second]->move(i.second.first, i.second.second);
			whatPlayerTurn = !whatPlayerTurn;
			update();
		}
	}
}

