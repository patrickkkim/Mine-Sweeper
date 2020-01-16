#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include "minegrid.h"
#include "event.h"

MineGrid::MineGrid(int r, int c, int maxMine, QWidget *parent) {
	row = r, col = c;
	mineMaxCount = maxMine;
	data = new Data(r, c, maxMine);
	grid = new QGridLayout(this);
	grid->setSpacing(0);

	//그리드에 버튼 행열로 생성함
	int pos = 0;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			QCustomPushButton *button = new QCustomPushButton(this);
			button->setFixedSize(28, 28);
			connect(button, &QCustomPushButton::clicked, grid, [this, i, j] { leftBtnClicked(i, j); });
			connect(button, &QCustomPushButton::rightClicked, grid, [this, i, j] { RightBtnClicked(i, j); });
			grid->addWidget(button, i, j);
			pos++;
		}
	}
}

// 버튼이 눌렷을시 버튼을 없애고 그자리에 지뢰데이터를 표시함
void MineGrid::leftBtnClicked(int x, int y) {
	if (isMine(x, y)) {
		openWidget(x, y);
		QLabel *label = new QLabel(this);
		QPixmap minePixmap("../icons/Mine.png");
		label->setPixmap(minePixmap.scaled(26, 26, Qt::KeepAspectRatio));
		grid->addWidget(label, x, y);
	}
	else {
		int adjCount = data->adjData[x][y];
		if (adjCount != 0) {
			openWidget(x, y);
			addAdjData(x, y, adjCount);
		}
		else {
			openAllBlankBtn(x, y);
		}
	}
}

void MineGrid::RightBtnClicked(int x, int y) {
	if (isButton(x, y) && isFlagged(x, y) == false) {
		flagBtn(x, y);
	}
}

void MineGrid::addAdjData(int x, int y, int count) {
	QLabel *label = new QLabel(QString::number(count), this);
	label->setAlignment(Qt::AlignCenter);
	grid->addWidget(label, x, y);
}

// 해당 빈칸과 서로 접하고있는 모든 빈칸을 열어놓음
void MineGrid::openAllBlankBtn(int x, int y) {
	if (isButton(x, y) == false) {
		return;
	}
	else if (data->adjData[x][y] != 0 && isMine(x, y) == false) {
		openWidget(x, y);
		addAdjData(x, y, data->adjData[x][y]);
	}
	else {
		openWidget(x, y);
		QLabel *label = new QLabel(this);
		grid->addWidget(label, x, y);
		openAllBlankBtn(x - 1, y);
		openAllBlankBtn(x + 1, y);
		openAllBlankBtn(x, y - 1);
		openAllBlankBtn(x, y + 1);
	}
}

// 해당 버튼을 열음
void MineGrid::openWidget(int x, int y) {
	QWidget *widget = grid->itemAtPosition(x, y)->widget();
	layout()->removeWidget(widget);
	delete widget;

	QLayoutItem *type = grid->itemAtPosition(x, y);
	if (type != 0) {
		widget = type->widget();
		layout()->removeWidget(widget);
		delete widget;
	}
}

void MineGrid::flagBtn(int x, int y) {
	QPixmap flagPixMap("../icons/flag.png");
	QCustomLabel *label = new QCustomLabel(this);
	connect(label, &QCustomLabel::rightClicked, grid, [this, x, y] { unFlag(x, y); });
	label->setPixmap(flagPixMap.scaled(26, 26, Qt::KeepAspectRatio));
	grid->addWidget(label, x, y);
}

void MineGrid::unFlag(int x, int y) {
	QWidget *flag = grid->itemAtPosition(x, y)->widget();
	flag->raise();
}

bool MineGrid::isFlagged(int x, int y) {
	QCustomLabel *type = qobject_cast<QCustomLabel*>(grid->itemAtPosition(x, y)->widget());
	if (type != nullptr) {
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

bool MineGrid::isMine(int x, int y) {
	if (data->mineData[x][y] == 1) {
		return true;
	}
	else {
		return false;
	}
}