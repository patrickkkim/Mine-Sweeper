#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include "minegrid.h"
#include "event.h"

MineGrid::MineGrid(int r, int c, int maxMine, QWidget *parent) {
	row = r, col = c;
	mineMaxCount = maxMine;
	remainingMine = mineMaxCount;
	isFirstMove = true;
	data = new Data(r, c, maxMine);
	grid = new QGridLayout();
	grid->setSpacing(0);
	changedSig = new TextChanged;
	gameOverSig = new GameOver;

	//그리드에 버튼 행열로 생성함
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			QCustomPushButton* button = data->getMineBtnData(i, j);
			button->setCheckable(true);
			connect(button, &QCustomPushButton::clicked, grid, [this, i, j] { leftBtnClicked(i, j); });
			connect(button, &QCustomPushButton::rightClicked, grid, [this, i, j] { RightBtnClicked(i, j); });
			grid->addWidget(button, i, j);
		}
	}
}

// 버튼이 눌렷을시 버튼을 없애고 그자리에 지뢰데이터를 표시함
void MineGrid::leftBtnClicked(int x, int y) {
	if (isFirstMove) {
		setFirstMove(x, y);
		isFirstMove = false;
	}
	else {
		openBtn(x, y);
	}
}

void MineGrid::RightBtnClicked(int x, int y) {
	if (isButton(x, y) && isFlagged(x, y) == false) {
		flagBtn(x, y);
	}
}

void MineGrid::middleBtnClicked(int x, int y) {
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if (isButton(x + i, y + j) && !(isFlagged(x + i, y + j))) {
				QCustomPushButton *button = data->getMineBtnData(x + i, y + j);
				button->setChecked(true);
			}
		}
	}
}

void MineGrid::middleBtnReleased(int x, int y) {
	int mineCount = 0;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if (isFlagged(x + i, y + j)) {
				mineCount++;
			}
		}
	}
	if (data->getAdjData(x, y) == mineCount) {
		for (int i = -1; i < 2; ++i) {
			for (int j = -1; j < 2; ++j) {
				if (isFlagged(x + i, y + j) == false && isButton(x + i, y + j)) {
					openBtn(x + i, y + j);
				}
			}
		}
	}
	else {
		for (int i = -1; i < 2; ++i) {
			for (int j = -1; j < 2; ++j) {
				if (isButton(x + i, y + j)) {
					QCustomPushButton *button = data->getMineBtnData(x + i, y + j);
					button->setChecked(false);
				}
			}
		}
	}
}

void MineGrid::addAdjLabel(int x, int y) {
	QCustomDataLabel *label = new QCustomDataLabel();
	label->setText(QString::number(data->getAdjData(x, y)));
	label->setStyleSheet("QCustomPushButton:hover:pressed{background-color:red;}");
	connect(label, &QCustomDataLabel::middlePressed, grid, [this, x, y] { middleBtnClicked(x, y); });
	connect(label, &QCustomDataLabel::middleReleased, grid, [this, x, y] { middleBtnReleased(x, y); });
	label->setAlignment(Qt::AlignCenter);
	grid->addWidget(label, x, y);
}

void MineGrid::addMineLabel(int x, int y) {
	QLabel *label = new QLabel();
	QPixmap minePixmap(":/MineSweeper/icons/Mine.png");
	label->setPixmap(minePixmap.scaled(26, 26, Qt::KeepAspectRatio));
	grid->addWidget(label, x, y);
}

// 해당 빈칸과 서로 접하고있는 모든 빈칸을 열어놓음
void MineGrid::openAllBlankBtn(int x, int y) {
	if (isButton(x, y) == false) {
		return;
	}
	else if (data->getAdjData(x, y) != 0 && data->isMine(x, y) == false) {
		removeButton(x, y);
		addAdjLabel(x, y);
	}
	else {
		removeButton(x, y);
		QLabel *label = new QLabel();
		grid->addWidget(label, x, y);
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				openAllBlankBtn(x + i, y + j);
			}
		}
	}
}

void MineGrid::openBtn(int x, int y) {
	if (data->isMine(x, y)) {
		removeButton(x, y);
		addMineLabel(x, y);
		gameOver();
	}
	else {
		if (data->getAdjData(x, y) != 0) {
			removeButton(x, y);
			addAdjLabel(x, y);
		}
		else {
			openAllBlankBtn(x, y);
		}
	}
	if (isVictory()) {
		gameOverSig->victoryEvent();
	}
}

void MineGrid::removeButton(int x, int y) {
	QWidget *widget = grid->itemAtPosition(x, y)->widget();
	this->removeWidget(widget);
	data->eraseMineBtnData(x, y);

	if (isFlagged(x, y)) {
		unFlag(x, y);
	}
}

void MineGrid::flagBtn(int x, int y) {
	QPixmap flagPixMap(":/MineSweeper/icons/Flag.png");
	QCustomIconLabel *label = new QCustomIconLabel();
	connect(label, &QCustomIconLabel::rightClicked, grid, [this, x, y] { unFlag(x, y); });
	label->setPixmap(flagPixMap.scaled(26, 26, Qt::KeepAspectRatio));
	grid->addWidget(label, x, y);
	data->setFlagData(x, y, label);
	changeRmnMineBox(QString::number(remainingMine), false);
}

void MineGrid::unFlag(int x, int y) {
	QCustomIconLabel *flag = data->getFlagData(x, y);
	layout()->removeWidget(flag);
	data->eraseFlagData(x, y);
	changeRmnMineBox(QString::number(remainingMine), true);
}

void MineGrid::setFirstMove(int x, int y) {
	data->setFirstMove(x, y);
	data->initAdjData();
	openAllBlankBtn(x, y);
}

bool MineGrid::isFlagged(int x, int y) {
	QLayoutItem *item = grid->itemAtPosition(x, y);
	if (item == 0) {
		return false;
	}
	if (data->getFlagData(x, y) != nullptr) {
		return true;
	}
	else {
		return false;
	}
}

// 해당 칸에 버튼이 있는지 확인
bool MineGrid::isButton(int x, int y) {
	if (x < 0 || y < 0 || x >= col || y >= row) {
		return false;
	}
	QPushButton *type = qobject_cast<QPushButton*>(grid->itemAtPosition(x, y)->widget());
	if (type != nullptr) {
		return true;
	}
	else {
		return false;
	}
}

bool MineGrid::isVictory() {
	if (data->getMineBtnCount() != mineMaxCount) {
		return false;
	}
	else {
		return true;
	}
}

void MineGrid::gameOver() {
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			if (isButton(i, j)) {
				openBtn(i, j);
			}
		}
	}
	gameOverSig->gameOverEvent();
}

void MineGrid::changeRmnMineBox(QString text, bool increase) {
	if (increase) {
		remainingMine++;
	}
	else {
		remainingMine--;
	}
	changedSig->changeValue(QString::number(remainingMine));
}

QGridLayout* MineGrid::getGrid() {
	return grid;
}

int MineGrid::getRemainingMine() {
	return remainingMine;
}